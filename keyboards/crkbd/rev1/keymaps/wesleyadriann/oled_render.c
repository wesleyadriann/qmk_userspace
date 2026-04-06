#include "quantum.h"
#include "oled_render.h"
#include "rgb_matrix.h"
#include "color.h"
#include "oled_driver.h"

// void oled_render_layer_state(void) {
//     oled_write_P(PSTR("L:"), false);
//
//     oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);
//
//     oled_write_ln_P(PSTR(""), false);
//     // oled_write_P(PSTR("-----"), false);
// }
//

void oled_render_layer_state(void) {
    char buf[16];

    uint8_t layer = get_highest_layer(layer_state);
    bool caps = host_keyboard_led_state().caps_lock;

    // ● = caps ON | ○ = caps OFF
        // caps ? 0xDF : 0xDE
    snprintf(buf, sizeof(buf), "L%d  %c",
        layer,
        caps ? 7 : 9
    );

    oled_write_ln(buf, false); // invertido = destaque
}

void oled_render_capslock(void) {
    oled_write_P(PSTR("C:"), false);

    if (host_keyboard_led_state().caps_lock) {
        oled_write_P(PSTR("  *"), false);
    } else {
        oled_write_P(PSTR("  _"), false);
    }

    oled_write_ln_P(PSTR(""), false);
    // oled_write_P(PSTR("-----"), false);
}

char     key_name_user = '_';
// uint16_t last_keycode;
uint8_t  last_row;
uint8_t  last_col;
uint32_t key_counter = 0;

static const char PROGMEM code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e','f', 'g', 'h', 'i', 'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_',
    '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    // save the row and column (useful even if we can't find a keycode to show)
    last_row = record->event.key.row;
    last_col = record->event.key.col;

    key_counter++;

    key_name_user     = '_';
    // last_keycode = keycode;
    if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count) {
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        } else {
            keycode = 0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10);
        }
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }
    if (keycode > ARRAY_SIZE(code_to_name)) {
        return;
    }

    // update keylog
    key_name_user = pgm_read_byte(&code_to_name[keycode]);
}

// static const char *depad_str(const char *depad_str, char depad_char) {
//     while (*depad_str == depad_char)
//         ++depad_str;
//     return depad_str;
// }

void oled_render_keylog(void) {

    oled_write_ln_P(PSTR(" Key\n"), false);

    oled_write_P(PSTR("  "), false);
    oled_write_char(key_name_user, false);
    // oled_write_ln_P(PSTR(""), false);
    //
    // oled_write_P(PSTR(" "), false);
    // oled_write_char('0' + last_row, false);
    // oled_write_P(PSTR("x"), false);
    // oled_write_char('0' + last_col, false);


    // const char *last_keycode_str = get_u16_str(last_keycode, ' ');
    // oled_write(depad_str(last_keycode_str, ' '), false);

    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("-----"), false);

    // oled_advance_page(true);
}

void oled_render_logo(void) {
    // static const char PROGMEM qmk_logo[] = {
    //     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    //     0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    //     0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    // };
    //
    // oled_write_P(qmk_logo, false);
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,124,252, 12, 12, 24, 24, 48, 96,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,240,128,128,128,128,128,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240, 48, 48, 99,204,192,224, 48, 24, 14,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 24, 24, 24, 24, 16, 16, 48, 48, 48, 96,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1, 48, 63, 48, 48, 48, 48,  0,  0,  0,  1,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  1,  1,  1,  1,  1, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31,  0,  0,  0,  0,  0,  1,  3, 14, 24, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 12, 12, 12,  8,  8,  8,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };

    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


void render_key_counter(void) {
    oled_write_ln_P(PSTR("Count"), false);

    char buf[16];
    snprintf(buf, sizeof(buf), "%5lu", key_counter);
    oled_write_ln(buf, false);
}


void render_rgb_mode(void) {
    // =====================
    // MODE
    // =====================
    //
    oled_write_ln_P(PSTR("_RGB_"), false);
    char buf[6];
    snprintf(buf, sizeof(buf), "M%03d", rgb_matrix_get_mode());
    oled_write_ln(buf, false);
    oled_write_ln_P(PSTR(""), false);
}

void render_rgb_status(void) {

    // =====================
    // BRIGHTNESS
    // =====================
    uint8_t val = rgb_matrix_get_val(); // 0–255

    // converte para 0–5
    uint8_t level = (val * 5) / 150;

    char bar[6] = ".....";

    if (level > 0 && level < sizeof bar) {
        bar[level - 1] = '|';
    }

    oled_write_ln(bar, false);

    // =====================
    // SPEED
    // =====================
    uint8_t speed_val = rgb_matrix_get_speed(); // 0–255

    // converte para 0–5
    uint8_t speed_level = (speed_val * 5) / 255;

    char bar_speed[6] = "_____";

    for (int i = 0; i < speed_level; i++) {
        bar_speed[i] = 16;
    }

    oled_write_ln(bar_speed, false);

    char buf[6];
    // =====================
    // HUE (0–255)
    // =====================
    snprintf(buf, sizeof(buf), "H%03d", rgb_matrix_get_hue());
    oled_write_ln(buf, false);
    oled_write_ln_P(PSTR(""), false);

   // =====================
    // SAT (0–255)
    // =====================
    snprintf(buf, sizeof(buf), "S%03d", rgb_matrix_get_sat());
    oled_write_ln(buf, false);
    oled_write_ln_P(PSTR(""), false);


}
