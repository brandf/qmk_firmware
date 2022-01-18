/* Copyright 2021 Sam Mohr <sam@mohr.codes>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "quantum.h"

enum layers {
    _COLEMAK = 0,
    /*_QWERTY,
    _GAME,*/
    _NAV,
    _NUM,
    _SYM,
    _FUN
};

#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT(
                                 KC_W,          KC_F,          KC_P,              KC_B,                     KC_J,               KC_L,               KC_U,             KC_Y,
        KC_Q,     LGUI_T(KC_A),  LALT_T(KC_R),  LCTL_T(KC_S),  LSFT_T(KC_T),      KC_G,                     KC_M,               RSFT_T(KC_N),       RCTL_T(KC_E),     RALT_T(KC_I),         RGUI_T(KC_O),    KC_SCLN,
                  KC_Z,          KC_X,          KC_C,          KC_D,              KC_V,                     KC_K,               KC_H,               KC_COMM,          KC_DOT,               KC_SLSH,
                                                               LT(_NUM, KC_TAB),  LT(_NAV, KC_SPC),         LT(_SYM, KC_BSPC),  LT(_FUN, KC_ENT)
    ),
    [_NAV] = LAYOUT(
                                 KC_NO,         KC_NO,         KC_NO,             KC_NO,                    KC_INS,             KC_PGUP,            KC_UP,            KC_NO,
        KC_NO,    KC_LGUI,       KC_LALT,       KC_LCTL,       KC_LSFT,           KC_NO,                    KC_HOME,            KC_LEFT,            KC_DOWN,          KC_RIGHT,             KC_END,          KC_NO,
                  U_UND,         U_CUT,         U_CPY,         U_PST,             U_RDO,                    KC_NO,              KC_PGDN,            KC_NO,            KC_NO,                KC_NO,
                                                               KC_NO,             KC_NO,                    KC_BSPC,            KC_ENT
    ),
    [_NUM] = LAYOUT(
                                 KC_NO,         KC_NO,         KC_NO,             KC_NO,                    KC_PSLS,            KC_P7,              KC_P8,            KC_P9,
        KC_NO,    KC_LGUI,       KC_LALT,       KC_LCTL,       KC_LSFT,           KC_NO,                    KC_COMM,            KC_P4,              KC_P5,            KC_P6,                KC_PPLS,        KC_PMNS,
                  U_UND,         U_CUT,         U_CPY,         U_PST,             U_RDO,                    KC_PDOT,            KC_P1,              KC_P2,            KC_P3,                KC_PAST,
                                                               KC_NO,             KC_NO,                    KC_0,               KC_PENT
    ),
    [_SYM] = LAYOUT(
                                 S(KC_COMM),    S(KC_9),       S(KC_0),           S(KC_DOT),                S(KC_1),            S(KC_2),            S(KC_3),          S(KC_4),
        KC_ESC,   KC_SLSH,       KC_QUOT,       S(KC_LBRC),    S(KC_RBRC),        S(KC_QUOT),               S(KC_BSLS),         KC_RSFT,            KC_RCTL,          KC_RALT,              KC_RGUI,        S(KC_5),
                  KC_BSLS,       KC_GRV,        KC_LBRC,       KC_RBRC,           S(KC_GRV),                S(KC_7),            S(KC_MINS),         KC_NO,            KC_NO,                S(KC_6),
                                                               KC_TAB,            KC_SPC,                   KC_NO,              KC_NO
    ),
    [_FUN] = LAYOUT(
                                 KC_F7,         KC_F8,         KC_F9,             KC_PSCR,                  KC_MUTE,            KC_VOLD,            KC_VOLU,          KC_MPLY,
        KC_F12,   KC_F11,        KC_F4,         KC_F5,         KC_F6,             KC_SCRL,                  KC_NO,              KC_RSFT,            KC_RCTL,          KC_RALT,              KC_RGUI,         KC_MEDIA_STOP,
                  KC_F10,        KC_F1,         KC_F2,         KC_F3,             KC_PAUS,                  KC_NO,              KC_MRWD,            KC_MPRV,          KC_MNXT,              KC_MFFD,
                                                               KC_TAB,            KC_SPC,                   KC_NO,              KC_NO
    ),
};
