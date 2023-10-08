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
};

//These also must be set for modifier keys: MO(4) -> change to L_RAISE while pressed
#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
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

  [L_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     RGB_TOG, QK_CLEAR_EEPROM,RGB_RMOD,RGB_MOD,XXXXXXX,XXXXXXX,                    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  RESET_COLOR, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  POMO_C,  POMO_T,\
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


enum pomodore_modes {
    POMO_RESET = -1,
    POMO_SESSION = 0,
    POMO_PAUSE = 1,
    POMO_BREAK = 2,
};
const int pomodore_times[] = {25,2,15};
enum pomodore_modes pomodore_mode = POMO_SESSION;
const uint16_t pomodore_sessions_until_bigbreak = 4;
uint16_t pomodore_sessions = 0;
bool pomodore_active = false;
bool pomodore_switch = false; // signals if we are ready to switch, so we don't constantly update leds
uint16_t pomodore_t = 0;
uint16_t pomodore_min = 0;



void pomodore_signal(enum pomodore_modes mode) {
    /* Signal that pomodore should switch state */
    switch (mode) {
        case POMO_SESSION:
            if (pomodore_sessions % pomodore_sessions_until_bigbreak == 0) {
                rgb_matrix_mode(RGB_MATRIX_BREATHING);
                rgb_matrix_sethsv(POMODORO_BREAK_HSV);
            } else {
                rgb_matrix_mode(RGB_MATRIX_BREATHING);
                rgb_matrix_sethsv(POMODORO_PAUSE_HSV);
            }
            break;
        case POMO_PAUSE:
        case POMO_BREAK:
            rgb_matrix_mode(RGB_MATRIX_BREATHING);
            rgb_matrix_sethsv(POMODORO_SESSION_HSV);
            break;
        case POMO_RESET:
            rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
            rgb_matrix_sethsv(STARTUP_HSV);
            break;

    }
}


void matrix_scan_user(void) {
    if (pomodore_active && ! pomodore_switch) {
        /* we count up to one minute. Timer is inacurate af so we correct here instead of at the minutes */
        if (timer_elapsed(pomodore_t)>48000) {
            pomodore_min++;
            pomodore_t = timer_read();
        }
        if (pomodore_min > pomodore_times[pomodore_mode]) {
            pomodore_switch = true;
            pomodore_signal(pomodore_mode);
        }
    }
}


void pomodore_cycle(void) {
    /* We have very limited state transitions:
     * Off -> SESSION
     * SESSION -> PAUSE/BREAK
     * PAUSE/BREAK -> SESSION
     * (SESSION/PAUSE/BREAK -> Off) <- stop function
     *
     * also check if we are in 'switch' state so we don't immediately start a new mode when we skip ahead
     * */
    if (!pomodore_active) {
        pomodore_t = 0;
        pomodore_min = 0;
        pomodore_active = true;
        pomodore_mode = POMO_SESSION;
        pomodore_sessions++;
        return;
    } else if (!pomodore_switch) {
        pomodore_switch = true;
        pomodore_signal(pomodore_mode);
        return;
    }
    if (pomodore_mode == POMO_SESSION) {
        pomodore_t = 0;
        pomodore_min = 0;
        pomodore_switch = false;
        if (pomodore_sessions % pomodore_sessions_until_bigbreak == 0) {
            pomodore_mode = POMO_BREAK;
        } else {
            pomodore_mode = POMO_PAUSE;
        }
        pomodore_signal(POMO_RESET);
        return;
    }
    if (pomodore_mode == POMO_BREAK || pomodore_mode == POMO_PAUSE) {
        pomodore_t = 0;
        pomodore_min = 0;
        pomodore_switch = false;
        pomodore_mode = POMO_SESSION;
        pomodore_sessions++;
        pomodore_signal(POMO_RESET);
        return;
    }
}

void pomodore_stop(void) {
    if (pomodore_active) {
        pomodore_t = 0;
        pomodore_min = 0;
        pomodore_active = false;
        pomodore_switch = false;
        pomodore_sessions = 0;
        pomodore_signal(POMO_RESET);
    }

}

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

uint8_t oled_logo_id = 0;
uint32_t startup_time = 0;

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
    random_tick();
    set_underglow(led_min,led_max);
    set_layer(led_min,led_max);
    return true;
}



#ifdef OLED_ENABLE
/* KEYBOARD PET START */

/* settings */
#    define MIN_WALK_SPEED      10
#    define MIN_RUN_SPEED       40

/* advanced settings */
#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#    define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

bool luna_is_sneaking = false;
bool luna_is_jumping  = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (luna_is_jumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (luna_is_sneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

/* KEYBOARD PET END */

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  } else {
    return OLED_ROTATION_270;
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
    // snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
    //     record->event.key.row, record->event.key.col,
    //     keycode, name);
    if (name != ' ') {
        snprintf(keylog_str, sizeof(keylog_str), "(%c)", name);
    } else {
        snprintf(keylog_str, sizeof(keylog_str), "   ");
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
        case L_LOWER:
            oled_write(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write(PSTR("Adj."), false);
            break;
        default:
            oled_write(PSTR("Unk."), false);
    }
    oled_set_cursor(0,5);
    oled_render_keylog();
    oled_set_cursor(0,7);
    if (pomodore_active) {
        oled_write(PSTR("     "), false);
        oled_set_cursor(0,7);
        switch (pomodore_mode) {
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
    if (pomodore_active){
        if (pomodore_switch) {
            oled_write("OVER",false);
        } else {
            //oled_write("     ",false);
            oled_set_cursor(0,8);
            volatile int p_size = sizeof(pomo_str);
            snprintf(pomo_str, p_size, "%-5.0d", pomodore_min);
            oled_write(pomo_str,false);
        }
    } else {
        oled_write("     ",false);
    }

    // oled_set_cursor(0,9);
    // char rand_str[5] = {};
    // snprintf(rand_str,sizeof(rand_str), "%d", oled_logo_id);
    // oled_write(rand_str, false);
    // oled_set_cursor(0,10);
    // char starttime_str[5] = {};
    // snprintf(starttime_str,sizeof(starttime_str), "%ld", startup_time);
    // oled_write(starttime_str, false);

    render_luna(0, 13);
}


bool oled_task_user(void) {
#    if OLED_TIMEOUT > 0
    /* the animation prevents the normal timeout from occuring */
    if (last_input_activity_elapsed() >= OLED_TIMEOUT) {
        //oled_off();
        return false;
    } else {
        oled_on();
    }
#    endif

    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        oled_render_one_of_logos(oled_logo_id);
    }
    return false;
}
//}}}

#endif // OLED_ENABLE

// ------------------------[Handle keypresses]

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* This function gets called before the actual handling is done!
     * Return true if normal handling should continue, else return false */
    switch (keycode) {
        // case TEST1:
        //     // for some reason mod1 + mod2 gets caught in this so ignore it
        //     return false;
        //     break;

        case POMO_C:
            if (record->event.pressed) {
                pomodore_cycle();
            }
            return false;
            break;

        case POMO_T:
            if (record->event.pressed) {
                pomodore_stop();
            }
            return false;
            break;

        case TG_8:
            static bool is_shifted;
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
                luna_is_sneaking = true;
            } else {
                luna_is_sneaking = false;
            }
            return true;
            break;
        case KC_SPC:
            if (record->event.pressed) {
                luna_is_jumping  = true;
                showedJump = false;
            } else {
                luna_is_jumping = false;
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





