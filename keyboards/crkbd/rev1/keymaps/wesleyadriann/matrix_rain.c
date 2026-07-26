// Copyright 2026 Wesley Adriann
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "matrix_rain.h"

#ifdef OLED_ENABLE

#    include "oled_driver.h"

// The OLED is mounted vertically.  Its 32-pixel framebuffer height is the
// visual width, while the 128-pixel framebuffer width is the visual height.
// A 3x5 glyph plus one blank pixel therefore gives eight rain columns.
#    define MATRIX_RAIN_COLUMNS (OLED_DISPLAY_HEIGHT / MATRIX_RAIN_COLUMN_WIDTH)
#    define MATRIX_RAIN_COLUMN_WIDTH 4
#    define MATRIX_RAIN_GLYPH_WIDTH 3
#    define MATRIX_RAIN_GLYPH_HEIGHT 5
#    define MATRIX_RAIN_GLYPH_STEP 6
#    define MATRIX_RAIN_FRAME_MS 50

// Small pseudo-katakana/numeric glyphs.  Keeping them in program memory saves
// RAM on the ATmega32U4.  Each byte is one 3-pixel-wide row, least-significant
// bit first.
static const uint8_t PROGMEM matrix_rain_glyphs[][MATRIX_RAIN_GLYPH_HEIGHT] = {
    {0x07, 0x05, 0x05, 0x05, 0x07},
    {0x02, 0x06, 0x02, 0x02, 0x07},
    {0x07, 0x01, 0x07, 0x04, 0x07},
    {0x07, 0x01, 0x03, 0x01, 0x07},
    {0x05, 0x05, 0x07, 0x01, 0x01},
    {0x07, 0x04, 0x07, 0x01, 0x07},
    {0x07, 0x04, 0x07, 0x05, 0x07},
    {0x07, 0x01, 0x02, 0x02, 0x02},
};

// Per-column state uses a 16-bit head position because the vertical canvas is
// 128 pixels tall.  The complete module uses 40 bytes of static RAM.
static int16_t matrix_rain_head[MATRIX_RAIN_COLUMNS];
static uint8_t matrix_rain_shape[MATRIX_RAIN_COLUMNS];
static uint8_t matrix_rain_glyph[MATRIX_RAIN_COLUMNS];
static uint32_t matrix_rain_prng_state = 0x6D2B79F5UL;
static uint16_t matrix_rain_timer;
static uint8_t  matrix_rain_frame;
static bool     matrix_rain_initialized;

// xorshift32 is compact, deterministic and avoids libc rand() on AVR.
static uint32_t matrix_rain_random(void) {
    uint32_t value = matrix_rain_prng_state;

    value ^= value << 13;
    value ^= value >> 17;
    value ^= value << 5;
    matrix_rain_prng_state = value;
    return value;
}

// Assign a newly spawned drop a random gap, speed, length and glyph.
static void matrix_rain_spawn(uint8_t column) {
    uint32_t value = matrix_rain_random();

    matrix_rain_head[column]  = -(int16_t)(value & 0x3FU);
    matrix_rain_shape[column] = (uint8_t)((value >> 5) & 0x0FU);
    matrix_rain_glyph[column] = (uint8_t)((value >> 9) & 0x07U);
}

// Maps the packed random value to a 2--4 pixel/frame fall speed.
static uint8_t matrix_rain_speed(uint8_t shape) {
    uint8_t speed = (shape & 0x03U) + 2;

    return speed == 5 ? 4 : speed;
}

// Returns whether one trail pixel survives the ordered-dither fade.
static bool matrix_rain_trail_pixel(uint8_t trail, uint8_t x, uint8_t y) {
    uint8_t dither = (uint8_t)(x + y + matrix_rain_frame);

    if (trail == 0) {
        return true; // The head is always fully lit.
    }
    if (trail == 1) {
        return (dither & 0x03U) != 0; // 75% brightness.
    }
    if (trail == 2) {
        return (dither & 0x01U) == 0; // 50% brightness.
    }
    return (dither & 0x03U) == 0; // 25% brightness.
}

// Sets one physical framebuffer pixel while preserving QMK's dirty tracking.
static void matrix_rain_write_pixel(uint8_t x, uint8_t y) {
    uint16_t             index = x + ((uint16_t)(y >> 3) * OLED_DISPLAY_WIDTH);
    oled_buffer_reader_t reader = oled_read_raw(index);

    oled_write_raw_byte(*reader.current_element | (1U << (y & 0x07U)), index);
}

// Draws the virtual 32x128 portrait canvas into the 128x32 framebuffer.  This
// rotates only the animation for the vertical OLED; oled_init_user() remains
// unchanged.  No second framebuffer is needed.
static void matrix_rain_render(void) {
    // Clear through the driver so it marks only changed bytes dirty.
    for (uint16_t index = 0; index < OLED_MATRIX_SIZE; ++index) {
        oled_write_raw_byte(0, index);
    }

    for (uint8_t column = 0; column < MATRIX_RAIN_COLUMNS; ++column) {
        uint8_t length = (matrix_rain_shape[column] >> 2) + 4;

        for (uint8_t trail = 0; trail < length; ++trail) {
            int16_t glyph_top = matrix_rain_head[column] - (int16_t)(trail * MATRIX_RAIN_GLYPH_STEP);

            for (uint8_t glyph_y = 0; glyph_y < MATRIX_RAIN_GLYPH_HEIGHT; ++glyph_y) {
                int16_t rain_y = glyph_top + glyph_y;

                if (rain_y < 0 || rain_y >= OLED_DISPLAY_WIDTH) {
                    continue;
                }

                for (uint8_t glyph_x = 0; glyph_x < MATRIX_RAIN_GLYPH_WIDTH; ++glyph_x) {
                    uint8_t rain_x = column * MATRIX_RAIN_COLUMN_WIDTH + glyph_x;

                    if (matrix_rain_trail_pixel(trail, rain_x, (uint8_t)rain_y) && (pgm_read_byte(&matrix_rain_glyphs[matrix_rain_glyph[column]][glyph_y]) & (1U << glyph_x))) {
                        matrix_rain_write_pixel((uint8_t)rain_y, OLED_DISPLAY_HEIGHT - 1 - rain_x);
                    }
                }
            }
        }
    }
}

void matrix_rain_task(void) {
    if (!matrix_rain_initialized) {
        for (uint8_t column = 0; column < MATRIX_RAIN_COLUMNS; ++column) {
            matrix_rain_spawn(column);
        }
        matrix_rain_timer       = timer_read();
        matrix_rain_initialized = true;
    }

    // oled_task_user() runs more often on non-split boards; retain 20 FPS.
    if (timer_elapsed(matrix_rain_timer) < MATRIX_RAIN_FRAME_MS) {
        return;
    }
    matrix_rain_timer = timer_read();
    ++matrix_rain_frame;

    for (uint8_t column = 0; column < MATRIX_RAIN_COLUMNS; ++column) {
        uint8_t length = (matrix_rain_shape[column] >> 2) + 4;

        matrix_rain_head[column] += matrix_rain_speed(matrix_rain_shape[column]);
        if (matrix_rain_head[column] > (OLED_DISPLAY_WIDTH + length * MATRIX_RAIN_GLYPH_STEP)) {
            matrix_rain_spawn(column);
        }
    }

    matrix_rain_render();
}

#endif // OLED_ENABLE
