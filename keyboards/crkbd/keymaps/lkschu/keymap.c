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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "rgb_matrix_layers.h"


#ifdef RGBLIGHT_ENABLE
    //Following line allows macro to read current RGB settings
    extern rgblight_config_t rgblight_config;
#endif

/* track custom keycodes, not needed for combikeys like shift-rightalt+x since there are special keys already defined */
enum custom_keycodes {
    TEST1,
    RESET_COLOR,
    EURO,
};

//These also must be set for modifier keys: MO(4) -> change to L_RAISE while pressed
#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   MO(2),  KC_SPC,     KC_ENT,   MO(4),  KC_LALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [L_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_BSLS, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_PGUP, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LGUI,RSA(KC_SCLN),RALT(KC_5),  KC_GRV, KC_MINS,  KC_EQL,                  KC_HOME,  KC_DEL,  KC_INS,  KC_END, KC_PGDN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, XXXXXXX,  KC_SPC,     KC_ENT, TG(8), KC_LALT \
                                      //`--------------------------'  `--------------------------'
    ),

  [L_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_BSLS, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_PGUP, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI,  TG(8),RALT(KC_S), KC_TILD, KC_UNDS, KC_PLUS,                     KC_HOME,  KC_DEL,  KC_INS,  KC_END, KC_PGDN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, TG(8),  KC_SPC,    KC_ENT,  XXXXXXX, KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [L_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     RGB_TOG, QK_CLEAR_EEPROM,RGB_RMOD,RGB_MOD,XXXXXXX,XXXXXXX,                    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  RESET_COLOR, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   TG(8), XXXXXXX,   XXXXXXX,    TG(8), KC_LALT \
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef ENABLE_UNDERGLOW
    bool underglowon = true;
#else
    bool underglowon = false;
#endif

#ifdef RGB_MATRIX_ENABLE
    bool rgb_matrix = true;
#else
    bool rgb_matrix = false;
#endif


void set_underglow(uint8_t min, uint8_t max) {
    // this sets underglow, ie the lower 6 leds
    if ( ! rgb_matrix) {
        return;
    }
    if ( underglowon ) {
        // rgb value
        uint8_t r = 10; uint8_t g = 15; uint8_t b = 10;
        // loop over all leds, check if flag is set to underglow, and set color
        for (uint8_t i = min; i < RGBLED_NUM && i < max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x02)) { // 0x02 == LED_FLAG_Underglow
                rgb_matrix_set_color(i, r, g, b);
            }
        }
    }
}


void keyboard_post_init_user(void) {
    //this is run once at start after setting everything else
    if ( ! rgb_matrix) {
        return;
    }
    rgb_matrix_sethsv(STARTUP_HSV);
}

// layer_state_t default_layer_state_set_user(layer_state_t state) {
//     activate_rgb_lightning_layer(0); // 0 := L_BASE
//     return state;
// }

//layer_state_t layer_state_set_user(layer_state_t state) {
//    switch (get_highest_layer(state)) {
//        case L_BASE:
//            activate_rgb_lightning_layer(0,0,54);
//        case L_LOWER:
//            activate_rgb_lightning_layer(1,0,54); // 1 := L_LOWER
//            break;
//        case L_RAISE:
//            activate_rgb_lightning_layer(2,0,54); // 2 := L_RAISE
//            break;
//        case L_ADJUST:
//            activate_rgb_lightning_layer(3,0,54); // 3 := L_ADJUST
//            break;
//    }
//    return state;
//}

void set_layer(uint8_t min, uint8_t max) {
    if ( ! rgb_matrix) {
        return;
    }
    switch (get_highest_layer(layer_state)) {
        case L_BASE:
            activate_rgb_lightning_layer(0,min, max); // 1 := L_BASE
            break;
        case L_LOWER:
            activate_rgb_lightning_layer(1,min, max); // 1 := L_LOWER
            break;
        case L_RAISE:
            activate_rgb_lightning_layer(2,min, max); // 2 := L_RAISE
            break;
        case L_ADJUST:
            activate_rgb_lightning_layer(3,min, max); // 3 := L_ADJUST
            break;
    }
}




bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    //gets called every cycle
    if ( ! rgb_matrix) {
        return false;
    }
    set_underglow(led_min,led_max);
    set_layer(led_min,led_max);
    return true;
}




//{{{ Oled stuff
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}


void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unknown"), false);
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
    if (keycode < 60) {
        name = code_to_name[keycode];
      }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
        record->event.key.row, record->event.key.col,
        keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    // default logo
    //static const char PROGMEM crkbd_logo[] = {
    //    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    //    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    //    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    //    0};
    //oled_write_P(crkbd_logo, false);

    // rune logo
    // logos can be generated from images on sites like this: https://javl.github.io/image2cpp/
    // (check bg color, canvas size, code output format and draw mode(propably vertical 1px) )
    static const char PROGMEM raw_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xa0, 0xe0, 0xe0, 0xc0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0xff,
        0xf9, 0xf1, 0xf1, 0xf9, 0x3d, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0,
        0xf0, 0xb8, 0x38, 0x1c, 0x1c, 0x0c, 0x0e, 0x0e, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
        0x0f, 0x0f, 0x1e, 0x3c, 0x3c, 0x78, 0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0,
        0xe0, 0xf0, 0x70, 0x38, 0x38, 0x1c, 0x0e, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xcf, 0xc7,
        0xc3, 0xc3, 0xc7, 0xcf, 0x7f, 0xfe, 0xfc, 0xf8, 0xf0, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03,
        0x03, 0x07, 0x0f, 0x0e, 0x0e, 0x1c, 0x3c, 0x3c, 0x78, 0x78, 0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0,
        0xc0, 0xe0, 0xe0, 0xf0, 0x78, 0x78, 0x3c, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x1f,
        0x1f, 0x3c, 0x38, 0x78, 0x70, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x03,
        0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
    /* This function gets called when handling keystokes? */
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}
//}}}


// ------------------------[Handle keypresses]

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* This function gets called before the actual handling is done!
     * Return true if normal handling should continue, else return false */
    switch (keycode) {
        case TEST1:
            // for some reason mod1 + mod2 gets caught in this so ignore it
            return false;
            break;

        case EURO:
            if (record->event.pressed) {
                SEND_STRING("str");
            } else {
                //on release
                SEND_STRING("release");
            }
            return false;
            break;

        case RESET_COLOR:
            if ( ! rgb_matrix  ){
                return false;
            }
            if (record->event.pressed) {
                rgb_matrix_sethsv(STARTUP_HSV);
            }
            return false;
            break;

        default:
            if (record->event.pressed) {
                set_keylog(keycode, record);
            }
            return true;
            break;
    }
}





#endif // OLED_ENABLE
