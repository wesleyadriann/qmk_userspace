#include "quantum.h"
#include "wpm.h"
#include "oled_render.h"

void print_layer(void) {
    oled_write_ln_P(PSTR("Layer"), false);

    oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);

    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("-----"), false);
}

void render_wpm(void) {
    oled_write_ln_P(PSTR("Wpm\n"), false);

    uint8_t wpm_val = get_current_wpm();

    if (wpm_val < 5) {
        oled_write("  0", false);
    } else {
        oled_write(get_u8_str(wpm_val, ' '), false);
    }

    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("-----"), false);
}

void render_capslock(void) {
    oled_write_ln_P(PSTR("Caps "), false);

    if (host_keyboard_led_state().caps_lock) {
        oled_write_P(PSTR("  *"), false);
    } else {
        oled_write_P(PSTR("  _"), false);
    }

}

