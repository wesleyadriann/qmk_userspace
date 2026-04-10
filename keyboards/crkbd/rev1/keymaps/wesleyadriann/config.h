#pragma once

// =====================
// SPLIT
// =====================
#define MASTER_RIGHT

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE

// =====================
// OLED
// =====================
#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#define OLED_TIMEOUT 60000
#define OLED_FADE_OUT


// =====================
// RGB MATRIX
// =====================
#ifdef RGB_MATRIX_ENABLE
// options
#   define RGB_MATRIX_LED_COUNT 54
#   define RGB_MATRIX_SPLIT { 27, 27 } // 54 LEDs total

#   define RGB_MATRIX_TIMEOUT OLED_TIMEOUT // number of milliseconds to wait until rgb automatically turns off
#   define RGB_MATRIX_SLEEP // turn off effects when suspended

#   define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
                                         //
#   undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.

#   define RGB_TRIGGER_ON_KEYDOWN      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards

// default values
#   define RGB_MATRIX_DEFAULT_ON true // Sets the default enabled state, if none has been set
#   define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR // Sets the default mode, if none has been set
#   define RGB_MATRIX_DEFAULT_HUE 0 // Sets the default hue value, if none has been set
#   define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
#   define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#   define RGB_MATRIX_DEFAULT_SPD 127 // Sets the default animation speed, if none has been set

// step
#   define RGB_MATRIX_HUE_STEP 16
#   define RGB_MATRIX_SAT_STEP 16
#   define RGB_MATRIX_VAL_STEP 30
#   define RGB_MATRIX_SPD_STEP 51

// animation
#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#endif
