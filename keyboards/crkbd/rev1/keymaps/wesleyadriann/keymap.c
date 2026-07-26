#include QMK_KEYBOARD_H
#include "quantum.h"
#include "oled_render.h"

enum layer_names {
    _0_MAIN,
    _1_AUX,
    _2_AUX_ALT,
    _3_NUMBERS_RGB,
    _4_SYMBOLS,
};

// custom keycodes
//  Turn on layer when held, kc when tapped
#define LT_03 LT(_3_NUMBERS_RGB, KC_ENT)
#define LT_04 LT(_4_SYMBOLS, KC_SPC)

//  mod-tap keys
//   left hand
#define LSHIFT_TAB LSFT_T(KC_TAB) // Left Shift when held, Tab when tapped
#define LALT_S LALT_T(KC_S)  // Left Alt when held, S when tapped
#define LGUI_F LGUI_T(KC_F)  // Left GUI when held, F when tapped

//   right hand
#define RCTL_SLSH RCTL_T(KC_SLSH)  // Right Control when held, / when tapped
#define RALT_DOT RALT_T(KC_DOT) // Right Alt when held, . when tapped

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌────────────┬───┬────────┬──────┬────────────┬───────┐       ┌───────┬────────────────┬──────┬──────────┬───────────┬──────┐
//    │  QK_GESC   │ q │   w    │  e   │     r      │   t   │       │   y   │       u        │  i   │    o     │     p     │ del  │
//    ├────────────┼───┼────────┼──────┼────────────┼───────┤       ├───────┼────────────────┼──────┼──────────┼───────────┼──────┤
//    │ LSHIFT_TAB │ a │ LALT_S │  d   │   LGUI_F   │   g   │       │   h   │       j        │  k   │    l     │     ;     │  '   │
//    ├────────────┼───┼────────┼──────┼────────────┼───────┤       ├───────┼────────────────┼──────┼──────────┼───────────┼──────┤
//    │    lctl    │ z │   x    │  c   │     v      │   b   │       │   n   │       m        │  ,   │ RALT_DOT │ RCTL_SLSH │ rsft │
//    └────────────┴───┴────────┼──────┼────────────┼───────┤       ├───────┼────────────────┼──────┼──────────┴───────────┴──────┘
//                              │ lgui │ MO(_1_AUX) │ LT_04 │       │ LT_03 │ MO(_2_AUX_ALT) │ bspc │
//                              └──────┴────────────┴───────┘       └───────┴────────────────┴──────┘
[_0_MAIN] = LAYOUT_split_3x6_3(
  QK_GESC    , KC_Q , KC_W   , KC_E    , KC_R       , KC_T  ,         KC_Y  , KC_U           , KC_I    , KC_O     , KC_P      , KC_DEL ,
  LSHIFT_TAB , KC_A , LALT_S , KC_D    , LGUI_F     , KC_G  ,         KC_H  , KC_J           , KC_K    , KC_L     , KC_SCLN   , KC_QUOT,
  KC_LCTL    , KC_Z , KC_X   , KC_C    , KC_V       , KC_B  ,         KC_N  , KC_M           , KC_COMM , RALT_DOT , RCTL_SLSH , KC_RSFT,
                               KC_LGUI , MO(_1_AUX) , LT_04 ,         LT_03 , MO(_2_AUX_ALT) , KC_BSPC
),

//    ┌─────┬─────┬─────┬────────┬────────┬─────┐       ┌──────┬──────┬─────┬──────┬─────┬─────┐
//    │     │  1  │  2  │   3    │   4    │  5  │       │  6   │  7   │  8  │  9   │  0  │ f11 │
//    ├─────┼─────┼─────┼────────┼────────┼─────┤       ├──────┼──────┼─────┼──────┼─────┼─────┤
//    │     │     │     │        │        │     │       │ left │ down │ up  │ rght │     │ f12 │
//    ├─────┼─────┼─────┼────────┼────────┼─────┤       ├──────┼──────┼─────┼──────┼─────┼─────┤
//    │     │     │     │ LCS(c) │ LCS(v) │     │       │      │      │     │      │     │     │
//    └─────┴─────┴─────┼────────┼────────┼─────┤       ├──────┼──────┼─────┼──────┴─────┴─────┘
//                      │        │        │     │       │      │      │     │
//                      └────────┴────────┴─────┘       └──────┴──────┴─────┘
[_1_AUX] = LAYOUT_split_3x6_3(
  KC_TRNS , KC_1    , KC_2    , KC_3      , KC_4      , KC_5    ,         KC_6    , KC_7    , KC_8    , KC_9     , KC_0    , KC_F11 ,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS ,         KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , KC_TRNS , KC_F12 ,
  KC_TRNS , KC_TRNS , KC_TRNS , LCS(KC_C) , LCS(KC_V) , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS,
                                KC_TRNS   , KC_TRNS   , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │  `  │     │     │  [  │  ]  │     │       │     │     │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │  (  │  )  │     │       │  -  │  +  │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │  {  │  }  │     │       │  _  │  =  │     │     │  \  │     │
//    └─────┴─────┴─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┴─────┴─────┘
//                      │     │     │     │       │     │     │     │
//                      └─────┴─────┴─────┘       └─────┴─────┴─────┘
[_2_AUX_ALT] = LAYOUT_split_3x6_3(
  KC_GRAVE , KC_TRNS , KC_TRNS , KC_LBRC , KC_RBRC , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS  , KC_TRNS , KC_TRNS , KC_LPRN , KC_RPRN , KC_TRNS ,         KC_MINS , KC_PLUS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS  , KC_TRNS , KC_TRNS , KC_LCBR , KC_RCBR , KC_TRNS ,         KC_UNDS , KC_EQL  , KC_TRNS , KC_TRNS , KC_BSLS , KC_TRNS,
                                 KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐       ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────┐
//    │     │  1  │  2  │  3  │  4  │  5  │       │    6    │    7    │    8    │    9    │    0    │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤       ├─────────┼─────────┼─────────┼─────────┼─────────┼─────┤
//    │     │     │     │     │     │     │       │ RM_TOGG │ RM_HUEU │ RM_SATU │ RM_VALU │ RM_SPDU │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤       ├─────────┼─────────┼─────────┼─────────┼─────────┼─────┤
//    │     │     │     │     │     │     │       │ RM_NEXT │ RM_HUED │ RM_SATD │ RM_VALD │ RM_SPDD │     │
//    └─────┴─────┴─────┼─────┼─────┼─────┤       ├─────────┼─────────┼─────────┼─────────┴─────────┴─────┘
//                      │     │     │     │       │         │         │         │
//                      └─────┴─────┴─────┘       └─────────┴─────────┴─────────┘
[_3_NUMBERS_RGB] = LAYOUT_split_3x6_3(
  KC_TRNS , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,         RM_TOGG , RM_HUEU , RM_SATU , RM_VALU , RM_SPDU , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,         RM_NEXT , RM_HUED , RM_SATD , RM_VALD , RM_SPDD , KC_TRNS,
                                KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS
),

//    ┌─────┬─────┬─────┬─────┬──────┬──────┐       ┌──────┬─────┬─────┬─────┬─────┬─────┐
//    │     │  !  │  @  │  #  │  $   │  %   │       │  ^   │  &  │  *  │     │     │     │
//    ├─────┼─────┼─────┼─────┼──────┼──────┤       ├──────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │      │ mply │       │ caps │     │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼──────┼──────┤       ├──────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │ vold │ volu │       │      │     │     │     │     │     │
//    └─────┴─────┴─────┼─────┼──────┼──────┤       ├──────┼─────┼─────┼─────┴─────┴─────┘
//                      │     │      │      │       │      │     │     │
//                      └─────┴──────┴──────┘       └──────┴─────┴─────┘
[_4_SYMBOLS] = LAYOUT_split_3x6_3(
  KC_TRNS , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,         KC_CIRC , KC_AMPR , KC_ASTR , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_MPLY ,         KC_CAPS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_VOLD , KC_VOLU ,         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                                KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS
)
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    } else {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_capslock();
        // oled_render_keylog();
        // render_key_counter();
        render_rgb_mode();
        render_rgb_status();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
}
