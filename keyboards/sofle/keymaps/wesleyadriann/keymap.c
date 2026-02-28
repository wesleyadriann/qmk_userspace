#include QMK_KEYBOARD_H
#include "oled_render.h"
#include "oled_space.h"

#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum layer_names {
    _0_MAIN,
    _1_SYMBOLS,
    _2_AUX,
    _3_AUX_ALT,
};

enum custom_keycodes {
    LAYER_1_3 = SAFE_RANGE, // tecla customizada
};


static uint16_t layer_timer;

static void handle_layer_tap_hold(keyrecord_t *record, uint8_t hold_layer, uint8_t tap_layer) {
    if (record->event.pressed) {
        layer_timer = timer_read();
        layer_on(hold_layer);
    } else {
        layer_off(hold_layer);
        if (timer_elapsed(layer_timer) < 200) {
            layer_invert(tap_layer);
        } else {
            layer_move(_0_MAIN);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER_1_3:
            handle_layer_tap_hold(record, _3_AUX_ALT, _1_SYMBOLS);
            return false;
    }
    return true;
}

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//        ┌─────────┬─────┬──────┬──────┬────────────┬─────┐                 ┌─────────────────────┬───────────┬──────┬──────┬───┬──────┐
//        │ QK_GESC │  1  │  2   │  3   │     4      │  5  │                 │          6          │     7     │  8   │  9   │ 0 │  -   │
//        ├─────────┼─────┼──────┼──────┼────────────┼─────┤                 ├─────────────────────┼───────────┼──────┼──────┼───┼──────┤
//        │   tab   │  q  │  w   │  e   │     r      │  t  │                 │          y          │     u     │  i   │  o   │ p │  =   │
//        ├─────────┼─────┼──────┼──────┼────────────┼─────┤                 ├─────────────────────┼───────────┼──────┼──────┼───┼──────┤
//        │  lsft   │  a  │  s   │  d   │     f      │  g  │                 │          h          │     j     │  k   │  l   │ ; │  '   │
//        ├─────────┼─────┼──────┼──────┼────────────┼─────┼──────┐   ┌──────┼─────────────────────┼───────────┼──────┼──────┼───┼──────┤
//        │  lctl   │  z  │  x   │  c   │     v      │  b  │ mply │   │ caps │          n          │     m     │  ,   │  .   │ / │ rsft │
//        └─────────┼─────┼──────┼──────┼────────────┼─────┼──────┘   └──────┼─────────────────────┼───────────┼──────┼──────┼───┼──────┘
//                  │     │ lalt │ lgui │ MO(_2_AUX) │ spc │                 │ LT(_3_AUX_ALT, ent) │ LAYER_1_3 │ bspc │ ralt │ \ │
//                  └─────┴──────┴──────┴────────────┴─────┘                 └─────────────────────┴───────────┴──────┴──────┴───┘
[_0_MAIN] = LAYOUT(
      QK_GESC , KC_1    , KC_2    , KC_3    , KC_4       , KC_5   ,                         KC_6                   , KC_7      , KC_8    , KC_9    , KC_0    , KC_MINS,
      KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R       , KC_T   ,                         KC_Y                   , KC_U      , KC_I    , KC_O    , KC_P    , KC_EQL ,
      KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F       , KC_G   ,                         KC_H                   , KC_J      , KC_K    , KC_L    , KC_SCLN , KC_QUOT,
      KC_LCTL , KC_Z    , KC_X    , KC_C    , KC_V       , KC_B   , KC_MPLY ,     KC_CAPS , KC_N                   , KC_M      , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
                KC_TRNS , KC_LALT , KC_LGUI , MO(_2_AUX) , KC_SPC ,                         LT(_3_AUX_ALT, KC_ENT) , LAYER_1_3 , KC_BSPC , KC_RALT , KC_BSLS
),

//        ┌─────┬─────┬─────┬─────┬─────┬─────┐               ┌─────┬─────┬─────┬─────┬─────┬─────┐
//        │     │ f1  │ f2  │ f3  │ f4  │ f5  │               │ f6  │ f7  │ f8  │ f9  │ f10 │ f11 │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼─────┼─────┤
//        │  `  │  1  │  2  │  3  │  4  │  5  │               │  6  │  7  │  8  │  9  │  0  │ f12 │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼─────┼─────┤
//        │     │  !  │  @  │  #  │  $  │  %  │               │  ^  │  &  │  *  │  (  │  )  │  |  │
//        ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//        │     │     │     │     │     │     │     │   │     │     │     │     │     │     │     │
//        └─────┼─────┼─────┼─────┼─────┼─────┼─────┘   └─────┼─────┼─────┼─────┼─────┼─────┼─────┘
//              │     │     │     │     │     │               │     │     │     │     │     │
//              └─────┴─────┴─────┴─────┴─────┘               └─────┴─────┴─────┴─────┴─────┘
[_1_SYMBOLS] = LAYOUT(
      KC_TRNS , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11 ,
      KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_F12 ,
      KC_TRNS , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                         KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_PIPE,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
),

//        ┌─────┬─────┬─────┬────────┬────────┬─────┐               ┌──────┬──────┬─────┬──────┬─────┬─────┐
//        │     │     │     │        │        │     │               │      │      │     │      │     │     │
//        ├─────┼─────┼─────┼────────┼────────┼─────┤               ├──────┼──────┼─────┼──────┼─────┼─────┤
//        │     │     │     │        │        │     │               │      │      │     │      │     │     │
//        ├─────┼─────┼─────┼────────┼────────┼─────┤               ├──────┼──────┼─────┼──────┼─────┼─────┤
//        │     │     │     │        │        │     │               │ left │ down │ up  │ rght │     │     │
//        ├─────┼─────┼─────┼────────┼────────┼─────┼─────┐   ┌─────┼──────┼──────┼─────┼──────┼─────┼─────┤
//        │     │     │     │ LCS(c) │ LCS(v) │     │     │   │     │      │      │     │      │     │     │
//        └─────┼─────┼─────┼────────┼────────┼─────┼─────┘   └─────┼──────┼──────┼─────┼──────┼─────┼─────┘
//              │     │     │        │        │     │               │      │      │     │      │     │
//              └─────┴─────┴────────┴────────┴─────┘               └──────┴──────┴─────┴──────┴─────┘
[_2_AUX] = LAYOUT(
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_TRNS , KC_TRNS,
      KC_TRNS , KC_TRNS , KC_TRNS , LCS(KC_C) , LCS(KC_V) , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                KC_TRNS , KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
),

//        ┌─────┬─────┬─────┬─────┬─────┬─────┐               ┌─────┬─────┬─────┬─────┬──────┬─────┐
//        │     │  !  │  @  │  #  │  $  │  %  │               │  ^  │  &  │  *  │  (  │  )   │  |  │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼──────┼─────┤
//        │     │     │     │  [  │  ]  │     │               │     │     │     │     │ pscr │ del │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼──────┼─────┤
//        │     │     │     │  (  │  )  │     │               │     │     │     │     │      │     │
//        ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼─────┼─────┼─────┼─────┼──────┼─────┤
//        │     │     │     │  {  │  }  │     │     │   │     │     │     │     │     │      │     │
//        └─────┼─────┼─────┼─────┼─────┼─────┼─────┘   └─────┼─────┼─────┼─────┼─────┼──────┼─────┘
//              │     │     │     │     │     │               │     │     │     │     │      │
//              └─────┴─────┴─────┴─────┴─────┘               └─────┴─────┴─────┴─────┴──────┘
[_3_AUX_ALT] = LAYOUT(
      KC_TRNS , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                         KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_PIPE,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_LBRC , KC_RBRC , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_PSCR , KC_DEL ,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_LPRN , KC_RPRN , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_LCBR , KC_RCBR , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
)
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    oled_clear();

    if (is_keyboard_master()) {
        print_layer();
        render_wpm();
        render_capslock();
    } else {
        render_space();
    }
    return false;
}
#endif // OLED_ENABLE


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
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
    return false;
}
#endif

