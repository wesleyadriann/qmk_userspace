/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


enum layer_names {
    _0_MAIN,
    _1_AUX,
    _2_AUX_ALT,
    _3_NUMBERS,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────┬───┬───┬──────┬────────────┬─────┐       ┌─────────────────────┬────────────────┬──────┬───┬───┬──────┐
//    │ QK_GESC │ q │ w │  e   │     r      │  t  │       │          y          │       u        │  i   │ o │ p │  =   │
//    ├─────────┼───┼───┼──────┼────────────┼─────┤       ├─────────────────────┼────────────────┼──────┼───┼───┼──────┤
//    │   tab   │ a │ s │  d   │     f      │  g  │       │          h          │       j        │  k   │ l │ ; │  '   │
//    ├─────────┼───┼───┼──────┼────────────┼─────┤       ├─────────────────────┼────────────────┼──────┼───┼───┼──────┤
//    │  lctl   │ z │ x │  c   │     v      │  b  │       │          n          │       m        │  ,   │ . │ / │ rsft │
//    └─────────┴───┴───┼──────┼────────────┼─────┤       ├─────────────────────┼────────────────┼──────┼───┴───┴──────┘
//                      │ lgui │ MO(_1_AUX) │ spc │       │ LT(_3_NUMBERS, ent) │ MO(_2_AUX_ALT) │ bspc │
//                      └──────┴────────────┴─────┘       └─────────────────────┴────────────────┴──────┘
[_0_MAIN] = LAYOUT_split_3x6_3(
  QK_GESC , KC_Q , KC_W , KC_E    , KC_R       , KC_T   ,         KC_Y                   , KC_U           , KC_I    , KC_O   , KC_P    , KC_EQL ,
  KC_TAB  , KC_A , KC_S , KC_D    , KC_F       , KC_G   ,         KC_H                   , KC_J           , KC_K    , KC_L   , KC_SCLN , KC_QUOT,
  KC_LCTL , KC_Z , KC_X , KC_C    , KC_V       , KC_B   ,         KC_N                   , KC_M           , KC_COMM , KC_DOT , KC_SLSH , KC_RSFT,
                          KC_LGUI , MO(_1_AUX) , KC_SPC ,         LT(_3_NUMBERS, KC_ENT) , MO(_2_AUX_ALT) , KC_BSPC
),

//    ┌─────┬─────┬─────┬────────┬────────┬─────┐       ┌──────┬──────┬─────┬──────┬─────┬─────┐
//    │     │  1  │  2  │   3    │   4    │  5  │       │  6   │  7   │  8  │  9   │  0  │     │
//    ├─────┼─────┼─────┼────────┼────────┼─────┤       ├──────┼──────┼─────┼──────┼─────┼─────┤
//    │     │     │     │        │        │     │       │ left │ down │ up  │ rght │     │     │
//    ├─────┼─────┼─────┼────────┼────────┼─────┤       ├──────┼──────┼─────┼──────┼─────┼─────┤
//    │     │     │     │ LCS(c) │ LCS(v) │     │       │      │      │     │      │     │     │
//    └─────┴─────┴─────┼────────┼────────┼─────┤       ├──────┼──────┼─────┼──────┴─────┴─────┘
//                      │        │        │     │       │      │      │     │
//                      └────────┴────────┴─────┘       └──────┴──────┴─────┘
[_1_AUX] = LAYOUT_split_3x6_3(
  KC_TRNS , KC_1    , KC_2    , KC_3      , KC_4      , KC_5    ,         KC_6    , KC_7    , KC_8    , KC_9     , KC_0    , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS ,         KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , LCS(KC_C) , LCS(KC_V) , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS,
                                KC_TRNS   , KC_TRNS   , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS
),

//    ┌──────┬─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │      │     │     │  [  │  ]  │     │       │     │     │     │     │     │     │
//    ├──────┼─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │ lctl │     │     │  (  │  ]  │     │       │  -  │  =  │     │     │     │     │
//    ├──────┼─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │ lsft │     │     │  {  │  }  │     │       │  _  │  +  │     │     │  |  │     │
//    └──────┴─────┴─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┴─────┴─────┘
//                       │     │     │     │       │     │     │     │
//                       └─────┴─────┴─────┘       └─────┴─────┴─────┘
[_2_AUX_ALT] = LAYOUT_split_3x6_3(
  KC_TRNS , KC_TRNS , KC_TRNS , KC_LBRC , KC_RBRC , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_LCTL , KC_TRNS , KC_TRNS , KC_LPRN , KC_RBRC , KC_TRNS ,         KC_MINS , KC_EQL  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_LSFT , KC_TRNS , KC_TRNS , KC_LCBR , KC_RCBR , KC_TRNS ,         KC_UNDS , KC_PLUS , KC_TRNS , KC_TRNS , KC_PIPE , KC_TRNS,
                                KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │     │  1  │  2  │  3  │  4  │  5  │       │  6  │  7  │  8  │  9  │  0  │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │     │     │       │     │     │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │     │     │       │     │     │     │     │     │     │
//    └─────┴─────┴─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┴─────┴─────┘
//                      │     │     │     │       │     │     │     │
//                      └─────┴─────┴─────┘       └─────┴─────┴─────┘
[_3_NUMBERS] = LAYOUT_split_3x6_3(
  KC_TRNS , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                                KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS
)
};

#ifdef ENCODER_MAP_ENABLE
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//   [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
//   [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
//   [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
//   [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
// };
#endif
