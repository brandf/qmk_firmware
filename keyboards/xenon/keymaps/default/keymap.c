/* Copyright 2020 Kyrre Havik Eriksen
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

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define M_LWR MO(_LOWER)
#define M_RSE MO(_RAISE)
#define L(kc) (LSFT(kc))
#define R(kc) (RALT(kc))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
      KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                         KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,
      KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                         KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
      KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                         KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,RSFT_T(KC_ENT),
                         KC_MUTE,KC_RALT,KC_LALT,KC_LGUI, KC_SPC,      KC_ENT, M_LWR,  KC_BSPC,M_RSE,  KC_MPLY,
                                 KC_DEL ,KC_PGDN,KC_PGUP,KC_ESC,      KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT
    ),
    [_LOWER] = LAYOUT(
      KC_BSLS,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
      KC_TRNS,   L(KC_1),L(KC_2),L(KC_3),L(KC_4),L(KC_5),                      L(KC_6), L(KC_7), L(KC_8), L(KC_9), L(KC_0), L(KC_MINS),
      KC_TRNS,   KC_GRV, KC_TRNS,L(KC_EQL),L(KC_RBRC),L(KC_BSLS),              KC_BSLS, KC_RBRC, KC_EQL,  KC_VOLD, KC_VOLU, KC_TRNS,
                         KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,       KC_ENT, KC_SPC,  KC_TRNS,  KC_TRNS, KC_RALT,
                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,       KC_ENT, KC_SPC,  KC_TAB,  KC_BSPC
    ),
    [_RAISE] = LAYOUT(
      KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                        KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
      KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
                         KC_LGUI,KC_DEL,KC_ENT,  KC_SPC, KC_ESC,       KC_ENT, KC_SPC,  KC_TAB,  KC_BSPC, KC_RALT,
                                 KC_DEL,KC_ENT,  KC_SPC, KC_ESC,       KC_ENT, KC_SPC,  KC_TAB,  KC_BSPC
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return OLED_ROTATION_270;
}

static void render_named_logo(void) {
  static const char PROGMEM raw_logo[] = {
    12, 60,252,252,252,236,236,140, 12, 28,248,192,  0,192,248,252,252,252,108, 12, 12,140,236, 60, 12,  0,  0,  0,248,252,252,252,236,204,204,204,204,204,204,204,204,204,204,204,204,140, 12,252,248,  0,  0,  0,252,252,252,252,236,236,236,204, 12, 60,240,192,  0,  0,  0,252,252,252,236,236, 12, 12, 12,252,248,  0,  0,192,224, 96, 48, 24, 24,140,140,132,196,196,196,196,132,140,140, 12, 24, 48, 48, 96,192,128,  0,  0,252,252,252,236,236,236,236,140, 28,120,224,128,  0,  0,252,252,252,252,236,236, 12, 12, 12,252,
    0,  0,  0,  3, 15,255,255,255,254,248,192,195,223,255,255, 63, 15,  1,224,248, 30,  7,  1,  0,  0,  0,  0,  0,255,255,255,255,255,255,  0,  0,  1, 63, 63, 51, 51, 51, 51, 51, 51, 51,243,  3,  1,  0,  0,  0,255,255,255,255,255,  1, 15,127,255,252,240,195, 15, 60,240,255,255,255,255,255,  0,  0,  0,255,255,254,255,255,255,127, 14,  2,195,247, 63, 31, 15, 15, 15, 15, 31, 63,255,255,254,252,248,224,  1,  3, 30,252,255,255,255,255,255,  3, 31,255,254,248,225,135, 30,120,255,255,255,255,255,255,  0,  0,  0,255, 
    0,  0,128,240,252,255,255,255, 63,  7,  1,227,127,255,255,255,248,224,  1,  7, 62,240,192,  0,  0,  0,  0,  0,255,255,255,255,255,255,  1,  3,  7,255,255,207,207,207,207,207,206,204,207,192,128,  0,  0,  0,255,255,255,255,255,  0,  0,  0,255,255, 15,127,255,252,240,227,143,127,255,255,  0,  0,  0,255,255, 63,255,255,255,254,240,192,131,135, 12, 24, 48, 48, 48, 48, 24, 28, 15,159,255, 63, 31,  7,128,192,120, 31,255,255,255,255,255,  0,  0,  0,255,255, 31,127,255,252,241,199, 31,127,255,255,  0,  0,  0,255,
    48, 62, 63, 63, 63, 63, 63, 56, 48, 60, 31,  3,  0,  3, 31, 63, 63, 63, 63, 60, 60, 56, 59, 63, 56,  0,  0,  0, 31, 63, 63, 63, 63, 63, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 56, 63, 31,  0,  0,  0, 63, 63, 63, 63, 63, 60, 56, 48, 63, 63,  0,  0,  0,  3, 31, 63, 63, 62, 61, 63, 60, 56, 48, 63, 31,  0,  0,  1,  7,  7, 15, 31, 31, 63, 63, 63, 62, 62, 62, 62, 63, 63, 63, 31, 31, 15, 14,  6,  3,  1,  0,  0, 63, 63, 63, 63, 63, 60, 56, 56, 63, 31,  0,  0,  1,  7, 31, 63, 63, 60, 63, 63, 60, 56, 48, 63
  };
  oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_status(void) {
  oled_write_P(PSTR("\n\n\n-----\nXENON\n-----\n\n"), false);

  // Host Keyboard Layer Status
  switch (get_highest_layer(layer_state)) {
      case _QWERTY:
          oled_write_P(PSTR("Base \n"), false);
          break;
      case _LOWER:
          oled_write_P(PSTR("Lower\n"), false);
          break;
      case _RAISE:
          oled_write_P(PSTR("Raise\n"), false);
          break;
      default:
          oled_write_P(PSTR("Undef\n"), false);
  }
  oled_write_P(PSTR("Layer\n"), false);
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_named_logo();
  }

  return true;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
	    tap_code(KC_VOLD);
        } else {
	    tap_code(KC_VOLU);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
	    tap_code(KC_PGDN);
        } else {
	    tap_code(KC_PGUP);
        }
    }

    return true;
}
#endif
