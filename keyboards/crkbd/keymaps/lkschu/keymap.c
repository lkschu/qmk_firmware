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
#include "oled_bg_image.h"
#include "luna.h"
#include "pomodore.h"
#include "config.h"

#define RGBLED_NUM 54


#ifdef RGBLIGHT_ENABLE
    //Following line allows macro to read current RGB settings
    extern rgblight_config_t rgblight_config;
#endif

/* track custom keycodes, not needed for combikeys like shift-rightalt+x since there are special keys already defined */
enum custom_keycodes {
    RESET_COLOR = SAFE_RANGE,  // NOTE: SAFE_RANGE guarantees a unique number!
    POMO_C,     // start/cycle pomodore mode
    POMO_T,     // stop pomodore
    TG_8,       // toggle layer 8 (only with shift)
    TG_ALT_LAYOUT,       // toggle alternative layouts
};

//These also must be set for modifier keys: MO(4) -> change to L_RAISE while pressed
#define L_BASE 0
#define L_ALTERNATIVE 1
#define L_LOWER 4
#define L_LOWER_ALT 5
#define L_RAISE 6
#define L_RAISE_ALT 7
#define L_ADJUST 8


#define randadd 53
#define randmul 181
#define randmod 167
/* 157 is the seed */
static uint16_t random_value = 157;
uint8_t clockbyte=0;



/* Hash function, see:
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function */
uint32_t fnv1(void * data, size_t numBytes){/*{{{*/
    const uint32_t FNV_PRIME = 0x01000193;
    const uint32_t FNV_OFFSET_BASIS = 0x811c9dc5;
    uint32_t hash = FNV_OFFSET_BASIS;
    unsigned char* byte_of_data = (unsigned char *)data;

    while (numBytes--) {
        hash = hash ^ *byte_of_data++;
        hash = hash * FNV_PRIME;
    }
    return hash;
}/*}}}*/

void random_tick(void) {
    //clockbyte = TCNT1 % 256;
    //clockbyte = TCNT0 % 256;
    clockbyte = timer_read() % 256;
    random_value = (random_value ^ clockbyte);
    random_value = ((random_value + randadd) * randmul) % randmod;
}

uint8_t random_u8(uint8_t max) {
    random_tick();
    uint32_t ret = (random_value ^ clockbyte);
    return fnv1(&ret,sizeof(ret)) % (max+1);
}



const uint16_t PROGMEM keymaps [][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   MO(L_LOWER),  KC_SPC,     KC_ENT,   MO(L_RAISE),  KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [L_ALTERNATIVE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I, KC_O   , KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      KC_LCTL,MO(L_LOWER_ALT), KC_SPC,  KC_ENT,MO(L_RAISE_ALT),KC_LALT \
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
                                          KC_LCTL, XXXXXXX,  KC_SPC,     KC_ENT, TG_8, KC_LALT \
                                      //`--------------------------'  `--------------------------'
    ),
  [L_LOWER_ALT] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,RALT(KC_S),KC_EXLM,  KC_AT, KC_HASH, KC_PLUS,                      KC_MINS,    KC_1, KC_2   , KC_3   , KC_BSLS, KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,RALT(KC_5), KC_DLR,KC_PERC, KC_CIRC, KC_UNDS,                      XXXXXXX, KC_4   ,   KC_5 ,KC_6    , KC_0   , KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LGUI,   KC_TILD, KC_AMPR, KC_ASTR, XXXXXXX, XXXXXXX,                       KC_EQL,  KC_7  ,  KC_8  ,  KC_9  , KC_PIPE, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, XXXXXXX,  KC_SPC,     KC_ENT, TG_8, KC_LALT \
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
                                          KC_LCTL, TG_8,  KC_SPC,    KC_ENT,  XXXXXXX, KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [L_RAISE_ALT] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, KC_MRWD, KC_MFFD, KC_MPLY, KC_LCBR,                      KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_CIRC, XXXXXXX, KC_QUOT, KC_DQUO, KC_LPRN,                      KC_RPRN, KC_LEFT, KC_DOWN,KC_UP   ,KC_RIGHT, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX, KC_LBRC,                      KC_RBRC, KC_HOME, KC_DOWN, KC_PGUP, KC_END , XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, TG_8,  KC_SPC,    KC_ENT,  XXXXXXX, KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [L_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     RGB_TOG, QK_CLEAR_EEPROM,RGB_RMOD,RGB_MOD,XXXXXXX,XXXXXXX,                    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  RESET_COLOR, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
TG_ALT_LAYOUT,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,  QK_BOOT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  POMO_C,  POMO_T,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   TG(8), XXXXXXX,   XXXXXXX,    TG(8), KC_LALT \
                                      //`--------------------------'  `--------------------------'
  )
};


void cycle_alternative_layouts(void) {
    layer_invert(L_ALTERNATIVE);
    // layer_xor(L_LOWER_ALT);
    // layer_xor(L_RAISE_ALT);
    return;
}



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




struct pomodore_instance pomo = {
    .sessions_until_bigbreak = 4,
    .mode = POMO_SESSION,
    .sessions = 0,
    .active = false,
    .switch_session = false,
    .t = 0,
    .min = 0,
    .times = {25,2,15}
};



void matrix_scan_user(void) {
    if (pomo.active && ! pomo.switch_session) {
        /* we count up to one minute. Timer is inacurate af so we correct here instead of at the minutes */
        if (timer_elapsed32(pomo.t) > 60500) {
            pomo.min++;
            pomo.t = timer_read32();
        }
        if (pomo.min >= pomo.times[pomo.mode]) {
            pomo.switch_session = true;
            pomodore_signal(&pomo, pomo.mode);
        }
    }
}



void set_underglow(uint8_t min, uint8_t max) {
    // this sets underglow, ie the lower 6 leds
    if ( ! rgb_matrix) {
        return;
    }
    if ( underglowon ) {
        return;
        // INFO: deprecated: Just handle indicators by using the per-layer rgb matrix
        // uint8_t r = 130; uint8_t g = 20; uint8_t b = 50;
        // // loop over all leds, check if flag is set to underglow, and set color
        // for (uint8_t i = min; i < RGBLED_NUM && i < max; i++) {
        //     if (HAS_FLAGS(g_led_config.flags[i], 0x02)) { // 0x02 == LED_FLAG_Underglow
        //         rgb_matrix_set_color(i, r, g, b);
        //     }
        // }
    }
}

uint8_t oled_logo_id = 0;
uint32_t startup_time = 0;


struct luna luna = { .is_jumping = false, .is_sneaking = false, ._anim_timer=0, ._current_frame=0, ._showed_jump=false, ._current_wpm=0 };


void keyboard_post_init_user(void) {
    //this is run once at start after setting everything else
    if ( ! rgb_matrix) {
        return;
    }
    uint32_t start = timer_read32();

    rgb_matrix_sethsv(STARTUP_HSV);
    rgb_matrix_set_speed(220);
    rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);

    /* 25000 iterations of useless calculations, just so the startup varies -slightly- and we get some rng...
     * takes about 200ms to boot */
    for (uint32_t i = 0; i<25000; i++) {
        random_tick();
        random_u8(255);
    }
    srand(random_u8(255));
    rand();
    rand();
    oled_logo_id = rand()%256;
    startup_time = timer_elapsed32(start);
}


void set_layer(uint8_t min, uint8_t max) {
    if ( ! rgb_matrix) {
        return;
    }
    switch (get_highest_layer(layer_state)) {
        case L_BASE:
            activate_rgb_lightning_layer(0,min, max);
            break;
        case L_ALTERNATIVE:
            activate_rgb_lightning_layer(1,min, max);
            break;
        case L_LOWER:
            activate_rgb_lightning_layer(2,min, max);
            break;
        case L_LOWER_ALT:
            activate_rgb_lightning_layer(3,min, max);
            break;
        case L_RAISE:
            activate_rgb_lightning_layer(4,min, max);
            break;
        case L_RAISE_ALT:
            activate_rgb_lightning_layer(5,min, max);
            break;
        case L_ADJUST:
            activate_rgb_lightning_layer(6,min, max);
            break;
    }
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    //gets called every cycle
    if ( ! rgb_matrix) {
        return false;
    }
    random_tick();
    set_underglow(led_min,led_max);
    set_layer(led_min,led_max);
    return true;
}


#ifdef OLED_ENABLE

/* status variables */
bool oled_enabled = true;


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  } else {
    return OLED_ROTATION_270;
  }
  return rotation;
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

    if (name != ' ') {
        snprintf(keylog_str, sizeof(keylog_str), "(%c)", name);
    } else {
        snprintf(keylog_str, sizeof(keylog_str), "-?-");
    }
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


static void print_status_narrow(void) {
    oled_set_cursor(0,1);
    oled_write("LAYER", false);
    oled_set_cursor(0,2);
    oled_write(PSTR("     "), false);
    oled_set_cursor(0,2);
    switch (get_highest_layer(layer_state)) {
        case L_BASE:
            oled_write(PSTR("Base"), false);
            break;
        case L_ALTERNATIVE:
            oled_write(PSTR("Colma"), false);
            break;
        case L_LOWER:
            oled_write(PSTR("Lower"), false);
            break;
        case L_LOWER_ALT:
            oled_write(PSTR("LoALT"), false);
            break;
        case L_RAISE:
            oled_write(PSTR("Raise"), false);
            break;
        case L_RAISE_ALT:
            oled_write(PSTR("RaALT"), false);
            break;
        case L_ADJUST:
            oled_write(PSTR("Adj."), false);
            break;
        default:
            oled_write(PSTR("ERROR"), false);
    }
    oled_set_cursor(0,5);
    oled_render_keylog();
    oled_set_cursor(0,7);
    if (pomo.active) {
        oled_write(PSTR("     "), false);
        oled_set_cursor(0,7);
        switch (pomo.mode) {
            case POMO_SESSION:
                oled_write("RUN",false);
                break;
            case POMO_PAUSE:
                oled_write("PAUSE",false);
                break;
            case POMO_BREAK:
                oled_write("BREAK",false);
                break;
            default:
                oled_write("UNK.",false);
                break;
        }
    } else {
        oled_write("     ",false);
    }
    oled_set_cursor(0,8);
    char pomo_str[5] = {};
    if (pomo.active){
        if (pomo.switch_session) {
            oled_write("OVER",false);
        } else {
            //oled_write("     ",false);
            oled_set_cursor(0,8);
            volatile int p_size = sizeof(pomo_str);
            snprintf(pomo_str, p_size, "%-5.0d", pomo.min);
            oled_write(pomo_str,false);
        }
    } else {
        oled_write("     ",false);
    }
    render_luna(0, 13, &luna);
}


bool oled_task_user(void) {
    if (!oled_enabled) {
        oled_off();
        return false;
    } else {
        oled_on();
    }

    luna._current_wpm   = get_current_wpm();
    luna.is_barking = host_keyboard_led_state().caps_lock;
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        oled_render_one_of_logos(oled_logo_id);
    }
    return false;
}


void housekeeping_task_user(void){
    // https://gist.github.com/drashna/79d14917f98f07e73071cbb391fcb654
    oled_enabled = (bool)(last_input_activity_elapsed() < OLED_TIMEOUT_CUSTOM);
}

#endif // OLED_ENABLE



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* This function gets called before the actual handling is done!
     * Return true if normal handling should continue, else return false */

    // WARN: hack:
    oled_enabled = true;

    bool is_shifted;
    switch (keycode) {
        case TG_ALT_LAYOUT:
            if (record->event.pressed) {
                cycle_alternative_layouts();
            }
            return false;
            break;

        case POMO_C:
            if (record->event.pressed) {
                pomodore_cycle(&pomo);
            }
            return false;
            break;

        case POMO_T:
            if (record->event.pressed) {
                pomodore_stop(&pomo);
            }
            return false;
            break;

        case TG_8:
            if (record->event.pressed) {
                is_shifted = get_mods() & MOD_MASK_SHIFT;
                if (is_shifted) {
                    del_mods(MOD_MASK_SHIFT);
                    layer_invert(L_ADJUST);
                }
            }
            return false;
            break;

        case RESET_COLOR:
            if ( ! rgb_matrix  ) {
                return false;
            }
            if (record->event.pressed) {
                rgb_matrix_sethsv(STARTUP_HSV);
            }
            return false;
            break;

        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                luna.is_sneaking = true;
            } else {
                luna.is_sneaking = false;
            }
            return true;
            break;
        case KC_SPC:
            if (record->event.pressed) {
                luna.is_jumping  = true;
                luna._showed_jump = false;
            } else {
                luna.is_jumping = false;
            }
            return true;
            break;

        default:
            if (record->event.pressed) {
                set_keylog(keycode, record);
            }
            return true;
            break;
    }
}

