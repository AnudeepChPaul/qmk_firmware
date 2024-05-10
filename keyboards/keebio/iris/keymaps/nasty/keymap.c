// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4, KC_5,                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL_T(KC_ESC), KC_A, KC_S, KC_D,   KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_BSPC,          KC_BSPC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, MO(2),   KC_ENT,                    KC_SPC,  MO(1),   KC_LALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(

      KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                             KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,

      LSFT(KC_TAB), KC_1, KC_2, KC_3, KC_4, KC_5,                                                 KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,

      LCTL_T(KC_ESC), KC_6, KC_7, KC_8, KC_9, KC_0,                                         KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,

      KC_LSFT, HYPR(KC_Z), MEH(KC_X), LCA_T(KC_C), KC_LPRN, KC_LBRC, KC_ASTR,       KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,

                                              KC_LGUI, KC_COMM, KC_UNDS,            KC_SPC, MO(1), KC_LALT
  ),

  [_RAISE] = LAYOUT(
      KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                                                 KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                                 KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
      LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G,                                         KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_BSPC,                  TG(3), KC_RBRC, KC_RPRN, KC_COMM, LCA_T(KC_DOT), MEH(KC_SLSH), HYPR(KC_MINS),
                          KC_LGUI, MO(2), KC_ENT,                           KC_MINS, KC_DOT, KC_SLSH
  ),

  [_ADJUST] = LAYOUT(
      KC_NO, RGB_HUD, RGB_HUI, RGB_M_P, RGB_M_B, KC_NO,                                     QK_BOOT, EE_CLR, DB_TOGG, KC_NO, KC_NO, KC_NO,
      RGB_TOG, RGB_VAD, RGB_MOD, RGB_VAI, RGB_M_R, RGB_M_SW,                                BL_TOGG, BL_OFF, BL_ON, KC_NO, KC_NO, NK_ON,
      KC_NO, RGB_SPD, RGB_RMOD, RGB_SPI, RGB_M_SN, RGB_M_K,                                 BL_STEP, BL_DOWN, BL_UP, KC_NO, KC_NO, KC_BSPC,
      KC_NO, RGB_SAD, KC_NO, RGB_SAI, RGB_M_X, RGB_M_G, KC_BSPC,                TG(3), BL_BRTG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                        KC_LGUI, MO(2), KC_ENT,                                             KC_SPC, MO(1), KC_LALT
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
