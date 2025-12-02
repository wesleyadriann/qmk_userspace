#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif


enum custom_keycodes {
    LAYER_TG_LT = SAFE_RANGE, // tecla customizada
};

static uint16_t layer_timer;

// Função principal
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER_TG_LT:
            if (record->event.pressed) {
                layer_timer = timer_read();
                layer_on(3);  // ativa layer 3 enquanto segura
            } else {
                layer_off(3);  // soltar → desativa layer 3
                if (timer_elapsed(layer_timer) < 200) {
                    // toque rápido → alterna layer 1
                    layer_invert(1);
                } else {
                    // segurou → volta pra layer 0
                    layer_move(0);
                }
            }
            return false; // não envia keycode padrão
    }
    return true;
}

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//        ┌─────────┬──────┬──────┬──────┬─────────────┬─────┐                 ┌─────┬───────┬──────┬──────┬──────┬──────┐
//        │ QK_GESC │  1   │  2   │  3   │      4      │  5  │                 │  6  │   7   │  8   │  9   │  0   │  -   │
//        ├─────────┼──────┼──────┼──────┼─────────────┼─────┤                 ├─────┼───────┼──────┼──────┼──────┼──────┤
//        │   tab   │  q   │  w   │  e   │      r      │  t  │                 │  y  │   u   │  i   │  o   │  p   │  =   │
//        ├─────────┼──────┼──────┼──────┼─────────────┼─────┤                 ├─────┼───────┼──────┼──────┼──────┼──────┤
//        │  lsft   │  a   │  s   │  d   │      f      │  g  │                 │  h  │   j   │  k   │  l   │  ;   │  '   │
//        ├─────────┼──────┼──────┼──────┼─────────────┼─────┼──────┐   ┌──────┼─────┼───────┼──────┼──────┼──────┼──────┤
//        │  lctl   │  z   │  x   │  c   │      v      │  b  │ mute │   │ mply │  n  │   m   │  ,   │  .   │  /   │ rsft │
//        └─────────┼──────┼──────┼──────┼─────────────┼─────┼──────┘   └──────┼─────┼───────┼──────┼──────┼──────┼──────┘
//                  │ lgui │ lalt │ caps │ LAYER_TG_LT │ spc │                 │ ent │ TG(2) │ bspc │ ralt │ rgui │
//                  └──────┴──────┴──────┴─────────────┴─────┘                 └─────┴───────┴──────┴──────┴──────┘
[0] = LAYOUT(
      QK_GESC , KC_1    , KC_2    , KC_3    , KC_4        , KC_5   ,                         KC_6   , KC_7  , KC_8    , KC_9    , KC_0    , KC_MINS,
      KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R        , KC_T   ,                         KC_Y   , KC_U  , KC_I    , KC_O    , KC_P    , KC_EQL ,
      KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F        , KC_G   ,                         KC_H   , KC_J  , KC_K    , KC_L    , KC_SCLN , KC_QUOT,
      KC_LCTL , KC_Z    , KC_X    , KC_C    , KC_V        , KC_B   , KC_MUTE ,     KC_MPLY , KC_N   , KC_M  , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
                KC_LGUI , KC_LALT , KC_CAPS , LAYER_TG_LT , KC_SPC ,                         KC_ENT , TG(2) , KC_BSPC , KC_RALT , KC_RGUI
),

//        ┌─────┬─────┬─────┬─────┬─────┬─────┐               ┌──────┬──────┬─────┬──────┬─────┬─────┐
//        │     │     │     │     │     │     │               │      │      │     │      │     │     │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├──────┼──────┼─────┼──────┼─────┼─────┤
//        │  `  │     │     │  [  │  ]  │     │               │      │      │     │      │     │     │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├──────┼──────┼─────┼──────┼─────┼─────┤
//        │     │     │     │  (  │  )  │     │               │ left │ down │ up  │ rght │     │     │
//        ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼──────┼──────┼─────┼──────┼─────┼─────┤
//        │     │     │     │  {  │  }  │     │     │   │     │      │      │     │      │     │     │
//        └─────┼─────┼─────┼─────┼─────┼─────┼─────┘   └─────┼──────┼──────┼─────┼──────┼─────┼─────┘
//              │     │     │     │     │     │               │      │      │     │      │     │
//              └─────┴─────┴─────┴─────┴─────┘               └──────┴──────┴─────┴──────┴─────┘
[1] = LAYOUT(
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
      KC_GRV  , KC_TRNS , KC_TRNS , KC_LBRC , KC_RBRC , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_LPRN , KC_RPRN , KC_TRNS ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_TRNS , KC_TRNS,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_LCBR , KC_RCBR , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
),

//        ┌─────┬─────┬─────┬─────┬─────┬─────┐               ┌─────┬─────┬─────┬─────┬─────┬─────┐
//        │     │ f1  │ f2  │ f3  │ f4  │ f5  │               │ f6  │ f7  │ f8  │ f9  │ f10 │ f11 │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼─────┼─────┤
//        │  `  │  1  │  2  │  3  │  4  │  5  │               │  6  │  7  │  8  │  9  │  0  │ f12 │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼─────┼─────┤
//        │     │  !  │  @  │  #  │  $  │  %  │               │  ^  │  &  │  *  │  (  │  )  │  |  │
//        ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//        │     │  =  │  -  │  +  │  {  │  }  │     │   │     │  [  │  ]  │  ;  │  :  │  \  │     │
//        └─────┼─────┼─────┼─────┼─────┼─────┼─────┘   └─────┼─────┼─────┼─────┼─────┼─────┼─────┘
//              │     │     │     │     │     │               │     │     │     │     │     │
//              └─────┴─────┴─────┴─────┴─────┘               └─────┴─────┴─────┴─────┴─────┘
[2] = LAYOUT(
      KC_TRNS , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11 ,
      KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_F12 ,
      KC_TRNS , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                         KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_PIPE,
      KC_TRNS , KC_EQL  , KC_MINS , KC_PLUS , KC_LCBR , KC_RCBR , KC_TRNS ,     KC_TRNS , KC_LBRC , KC_RBRC , KC_SCLN , KC_COLN , KC_BSLS , KC_TRNS,
                KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
),

//        ┌─────┬─────┬─────┬─────┬─────┬─────┐               ┌──────┬──────┬─────┬──────┬──────┬─────┐
//        │     │     │     │     │     │     │               │      │      │     │      │ pscr │ del │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├──────┼──────┼─────┼──────┼──────┼─────┤
//        │     │     │     │     │     │     │               │      │      │     │      │      │     │
//        ├─────┼─────┼─────┼─────┼─────┼─────┤               ├──────┼──────┼─────┼──────┼──────┼─────┤
//        │     │     │     │     │     │     │               │ left │ down │ up  │ rght │      │     │
//        ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼──────┼──────┼─────┼──────┼──────┼─────┤
//        │     │     │     │     │     │     │     │   │     │      │      │     │      │      │     │
//        └─────┼─────┼─────┼─────┼─────┼─────┼─────┘   └─────┼──────┼──────┼─────┼──────┼──────┼─────┘
//              │     │     │     │     │     │               │      │      │     │      │      │
//              └─────┴─────┴─────┴─────┴─────┘               └──────┴──────┴─────┴──────┴──────┘
[3] = LAYOUT(
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_PSCR , KC_DEL ,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_TRNS , KC_TRNS,
      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
)
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

