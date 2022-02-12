/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

/* obligatory */
#ifdef VENDOR_ID
    #undef VENDOR_ID
    #define VENDOR_ID    0x4269
#endif
#ifdef PRODUCT_ID
    #undef PRODUCT_ID
    #define PRODUCT_ID   0x0420
#endif
#ifdef DEVICE_VER
    #undef DEVICE_VER
    #define DEVICE_VER   0x0069
#endif
#ifdef MANUFACTURER
    #undef MANUFACTURER
    #define MANUFACTURER "Corne"
#endif
#ifdef PRODUCT
    #undef PRODUCT
    #define PRODUCT      "Keyboard crkbd"
#endif


#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define TAPPING_FORCE_HOLD
//#define TAPPING_TERM 100

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 100
    #define RGBLIGHT_HUE_STEP 4
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
#endif

#ifdef RGB_MATRIX_ENABLE
    //required by rgb matrix indicators
    #define SPLIT_LAYER_STATE_ENABLE

    #define RGBLIGHT_LIMIT_VAL 100
    #define RGBLIGHT_HUE_STEP 4
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8

    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGBLIGHT_SLEEP
    #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
    #define RGB_DISABLE_TIMEOUT 600000    // in ms -> 600000ms = 10min

    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE      // Static single hue, pulses keys hit to shifted hue then fades to current hue
    #define ENABLE_RGB_MATRIX_HUE_BREATHING       // Hue shifts up a slight ammount at the same time, then shifts back
    #define ENABLE_RGB_MATRIX_SOLID_COLOR = 1     // Static single hue, no speed support
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   // Pulses keys hit to hue & value then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_HUE_WAVE            // Hue shifts up a slight ammount and then back down in a wave to the right
    #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL       // Single hue fractal filled keys pulsing horizontally out to edges
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // Full gradient scrolling left to right
    #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT    // Static gradient left to right, speed controls how much gradient changes
    #define ENABLE_RGB_MATRIX_BREATHING           // Single hue brightness cycling animation
    #define ENABLE_RGB_MATRIX_BAND_SAT        // Single hue band fading saturation scrolling left to right
    //#define ENABLE_RGB_MATRIX_ALPHAS_MODS         // Static dual hue, speed is hue for secondary hue
    #define ENABLE_RGB_MATRIX_SPLASH
    #define ENABLE_RGB_MATRIX_SOLID_SPLASH

    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE
    //these are mostly guesses...
    //take a color picker, like https://alloyui.com/examples/color-picker/hsv.html
    //calculate HSV so that max hsv is 255,255,255 instead of 360,100,100
    //then adjust hue and value accordingly, if rgb and hsv don't match
    // known values:
    // - cyan rgb(15,40,40) = hsv(138,160,40)
    // - mint rgb(15,40,25) = hsv(118,160,40
    #define RGB_MATRIX_STARTUP_HUE 95
    #define RGB_MATRIX_STARTUP_SAT 160
    #define RGB_MATRIX_STARTUP_VAL 40
    #define RGB_MATRIX_STARTUP_SPD 120

    // custom constants:
    #define ENABLE_UNDERGLOW

#endif


//// incompatible with lto (link time opti), disabled to save space
//// see: https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
////#define NO_ACTION_MACRO
////#define NO_ACTION_FUNCTION
// disable debugging :L
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT


#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
