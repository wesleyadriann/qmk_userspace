
// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef SWAP_HANDS_ENABLE

__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] =
    // The LAYOUT macro could work for this, but it was harder to figure out the
    // identity using it.

    // This is the identity layout.
/*
{
    { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0} },
    { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1} },
    { {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2} },
    { {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3} },
    { {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4} },

    { {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5} },
    { {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6} },
    { {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7} },
    { {0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8} },
    { {0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9} },
};
*/

    // This is the mirror, q <-> p, w <-> o, etc...
{
 { {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5} },
 { {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6} },
 { {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7} },
 { {0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8} },
 { {0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9} },

 { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0} },
 { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1} },
 { {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2} },
 { {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3} },
 { {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4} },
};

#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {1, 0};
#    endif

#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
    // if (is_keyboard_master()) {
    // }
    // return rotation;
}

// static void render_logo(void) {
//     static const char PROGMEM qmk_logo[] = {
//         0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
//         0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
//         0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
//     };
//     oled_write_P(qmk_logo, false);
// }

static void render_logo(void) {
    static const unsigned char PROGMEM raw_logo[] = {
        63, 63,199,251,251, 62,222,198,251,255,255,255,255,255,255,255,255,255,255,255,255,255,255,251,255,198, 62, 62,251,199,199, 63,252,252,199,191,191,126,233,193,207,255,191,191,191,191,191,191,191,191,191,191,191,191,191,239,207,225,126,126,191,231,231,252,255,255,255,255,255,  0,255,255,127, 63, 31, 31,127,127,255,255,255,255,255,127, 31, 31, 31,127,127,255,  0,  0,255,255,255,255,255,255,255,127,127, 56,223,199, 60, 56, 56, 56, 60, 60, 63, 63, 63, 63, 63,124,120, 56, 56,
        60,254,199,248,248,255,255,255,255,255,255,255,254,254,247,228,204,  0, 56,184,119, 73, 73,  0,  0,  0,  0,  0,  0,  0,  0,128,  7,111,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252,253,129, 18, 16,  0,  0,128,128,  0,  0,  0,  0,  0,  9,128,128, 79, 63, 63,255,255,255,255,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void print_status_narrow(void) {

    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("L: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("0"), false);
            break;
        case 1:
            oled_write_P(PSTR("1"), false);
            break;
        case 2:
            oled_write_P(PSTR("2"), false);
            break;
        case 3:
            oled_write_P(PSTR("3"), false);
            break;
        default:
            oled_write_P(PSTR("*"), false);
    }

    oled_write_P(PSTR("\n\n"), false);

    // switch (get_highest_layer(layer_state)) {
    //     case 0:
    //         oled_write_ln_P(PSTR("Qwrt"), false);
    //         break;
    //     case 1:
    //         oled_write_ln_P(PSTR("Clmk"), false);
    //         break;
    //     default:
    //         oled_write_P(PSTR("Mod\n"), false);
    //         break;
    // }
    // oled_write_P(PSTR("\n\n"), false);
    // oled_write_ln_P(PSTR("LAYER"), false);
    // switch (get_highest_layer(layer_state)) {
    //     case 0:
    //     case 1:
    //         oled_write_P(PSTR("Base\n"), false);
    //         break;
    //     case 2:
    //         oled_write_P(PSTR("Lower"), false);
    //         break;
    //     case 3:
    //         oled_write_P(PSTR("Raise"), false);
    //         break;
    //     case 4:
    //         oled_write_P(PSTR("Adjust"), false);
    //         break;
    //     default:
    //         oled_write_ln_P(PSTR("Undef"), false);
    // }
    // oled_write_P(PSTR("\n\n"), false);
    // led_t led_usb_state = host_keyboard_led_state();
    // oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

void render_capslock(void) {

    oled_write_ln_P(PSTR("\nCAPS "), false);
    if (host_keyboard_led_state().caps_lock) {
        oled_write_P(PSTR(" ON"), false);
    } else {
        oled_write_P(PSTR(" OFF"), false);
    }

    oled_write_ln_P(PSTR("\n\n"), false);
}


bool oled_task_kb(void) {
    // if (!oled_task_user()) {
    //     return false;
    // }

    oled_clear();
    print_status_narrow();
    render_capslock();
    render_logo();

    // if (is_keyboard_master()) {
    //     print_status_narrow();
    // } else {
    //     render_logo();
    // }
    return true;
}

#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MEDIA_NEXT_TRACK);
        } else {
            tap_code(KC_MEDIA_PREV_TRACK);
        }
    }
    return true;
}
#endif
