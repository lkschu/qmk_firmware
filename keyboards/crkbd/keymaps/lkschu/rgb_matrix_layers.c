#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include QMK_KEYBOARD_H
#include "rgb_matrix_layers.h"
#include "colors.h"
#include "quantum.h"

#include <math.h>


/** WARN: STARTUP_HSV is defined in the header! */


bool rgb_matrix_layers_initialized = false;

#define HUE_SHIFT_1ST_HALF 32 // Shift the non-master-side hue down by this number to correct color mismatches


typedef struct {
    double h; // 0 - 360
    double s; // 0 - 1
    double v; // 0 - 1
} HSV_base;

typedef struct {
    uint8_t r; // 0 - 255
    uint8_t g; // 0 - 255
    uint8_t b; // 0 - 255
} RGB_base;

HSV_base hexrgb_to_hsv(rgb_color rgb) {
    double r = rgb.red / 255.0;
    double g = rgb.green / 255.0;
    double b = rgb.blue / 255.0;

    double max = fmax(r, fmax(g, b));
    double min = fmin(r, fmin(g, b));
    double delta = max - min;

    HSV_base out;

    // Hue
    if (delta == 0) {
        out.h = 0;
    } else if (max == r) {
        out.h = 60 * fmod(((g - b) / delta), 6.0);
    } else if (max == g) {
        out.h = 60 * (((b - r) / delta) + 2.0);
    } else {
        out.h = 60 * (((r - g) / delta) + 4.0);
    }
    if (out.h < 0) out.h += 360;

    // Saturation
    out.s = (max == 0) ? 0 : (delta / max);

    // Value
    out.v = max;
    return out;
}

// already implemented in quantum
RGB_base hsv_to_hexrgb(HSV_base hsv) {
    double C = hsv.v * hsv.s;
    double X = C * (1 - fabs(fmod(hsv.h / 60.0, 2) - 1));
    double m = hsv.v - C;

    double r_prime, g_prime, b_prime;

    if (hsv.h < 60) {
        r_prime = C; g_prime = X; b_prime = 0;
    } else if (hsv.h < 120) {
        r_prime = X; g_prime = C; b_prime = 0;
    } else if (hsv.h < 180) {
        r_prime = 0; g_prime = C; b_prime = X;
    } else if (hsv.h < 240) {
        r_prime = 0; g_prime = X; b_prime = C;
    } else if (hsv.h < 300) {
        r_prime = X; g_prime = 0; b_prime = C;
    } else {
        r_prime = C; g_prime = 0; b_prime = X;
    }

    RGB_base out;
    out.r = (int)round((r_prime + m) * 255);
    out.g = (int)round((g_prime + m) * 255);
    out.b = (int)round((b_prime + m) * 255);
    return out;
}


struct rgb_matrix_layer_atom from_rgb_color(uint8_t start, uint8_t amount, rgb_color rgb ) {
    // HSV_base hsv = hexrgb_to_hsv(rgb);
    // // Those led just don't have the same color intensities, i just can't fix this with a hue shift! :(
    // if (start <= 6) {
    //     hsv.h = (hsv.h - 1.0);
    // } else if (start <= 26) {
    //     hsv.h = (hsv.h + 1.0);
    // }

    // if (hsv.h < 0.0) {
    //     hsv.h += 360.0;
    // }
    // if (hsv.h > 360.0) {
    //     hsv.h -= 360.0;
    // }
    // RGB_base rgb_shifted = hsv_to_hexrgb(hsv);
    RGB_base rgb_shifted;
    rgb_shifted.r = rgb.red;
    rgb_shifted.g = rgb.green;
    rgb_shifted.b = rgb.blue;

    if (start <=26) {
        rgb_shifted.b = (uint8_t) ( ((double) rgb_shifted.b) * 0.60);
    } else {
        double new_blue = ((double) rgb_shifted.b) * 1.40;
        if (new_blue > 255.0) {
            new_blue = 255.0;
        }
        rgb_shifted.b = (uint8_t) new_blue;
    }

    struct rgb_matrix_layer_atom return_value = { start, amount, rgb_shifted.r, rgb_shifted.g, rgb_shifted.b };
    return return_value;
}








// Create arrays with associated length
struct rgb_matrix_layer led_layer_base;
struct rgb_matrix_layer led_layer_colmak;
struct rgb_matrix_layer led_layer_lower;
struct rgb_matrix_layer led_layer_lower_alt;
struct rgb_matrix_layer led_layer_raise;
struct rgb_matrix_layer led_layer_raise_alt;
struct rgb_matrix_layer led_layer_adjust;
// Now define the array of layers. Later layers take precedence
struct rgb_matrix_layers rgb_matrix_layers;


void init_matrix_rgb_layers(void) {
    if (rgb_matrix_layers_initialized) {
        return;
    }

    /** Define your lightning layers here */
    struct rgb_matrix_layer_atom * led_layer_base_a = malloc(sizeof(struct rgb_matrix_layer_atom)*10);
    led_layer_base_a[0] = from_rgb_color(0, 6,         C_CYAN_30C);        //underglow
    led_layer_base_a[1] = from_rgb_color(6, 1,         C_PURPLE_30F);      //alphas
    led_layer_base_a[3] = from_rgb_color(13, 1,        C_PURPLE_30F);      //alphas
    led_layer_base_a[2] = from_rgb_color(7, 6,         C_VIOLET_30D);      // normal keys
    led_layer_base_a[4] = from_rgb_color(14, 13,       C_VIOLET_30D);    // normal keys

    led_layer_base_a[5] = from_rgb_color(0+27, 6,      C_CYAN_30C);
    led_layer_base_a[6] = from_rgb_color(6+27, 1,      C_PURPLE_30F);
    led_layer_base_a[8] = from_rgb_color(13+27, 1,     C_PURPLE_30F);
    led_layer_base_a[7] = from_rgb_color(7+27, 6,      C_VIOLET_30D);      // normal keys
    led_layer_base_a[9] = from_rgb_color(14+27, 13,    C_VIOLET_30D);    // normal keys
    led_layer_base.atoms = led_layer_base_a;
    led_layer_base.len = 10;

    struct rgb_matrix_layer_atom * led_layer_base_colemak_a = malloc(sizeof(struct rgb_matrix_layer_atom)*10);
    led_layer_base_colemak_a [0] = from_rgb_color(0, 6,         C_ROSE_30C);        //underglow
    led_layer_base_colemak_a [1] = from_rgb_color(6, 1,         C_PURPLE_30F);      //alphas
    led_layer_base_colemak_a [3] = from_rgb_color(13, 1,        C_PURPLE_30F);      //alphas
    led_layer_base_colemak_a [2] = from_rgb_color(7, 6,         C_PURPLE_30C);      // normal keys
    led_layer_base_colemak_a [4] = from_rgb_color(14, 13,       C_PURPLE_30C);    // normal keys

    led_layer_base_colemak_a[5] = from_rgb_color(0+27, 6,      C_ROSE_30C);
    led_layer_base_colemak_a[6] = from_rgb_color(6+27, 1,      C_PURPLE_30F);
    led_layer_base_colemak_a[8] = from_rgb_color(13+27, 1,     C_PURPLE_30F);
    led_layer_base_colemak_a[7] = from_rgb_color(7+27, 6,      C_PURPLE_30C);      // normal keys
    led_layer_base_colemak_a[9] = from_rgb_color(14+27, 13,    C_PURPLE_30C);    // normal keys
    led_layer_colmak.atoms = led_layer_base_colemak_a;
    led_layer_colmak.len = 10;

    struct rgb_matrix_layer_atom * led_layer_lower_a = malloc(sizeof(struct rgb_matrix_layer_atom)*10);
    led_layer_lower_a[0] = from_rgb_color(0, 6,         C_CYAN_30C);        //underglow
    led_layer_lower_a[1] = from_rgb_color(6, 1,         C_PINK_30F);      //alphas
    led_layer_lower_a[3] = from_rgb_color(13, 1,        C_PINK_30F);      //alphas
    led_layer_lower_a[2] = from_rgb_color(7, 6,         C_FUCHSIA_30C);      // normal keys
    led_layer_lower_a[4] = from_rgb_color(14, 13,       C_FUCHSIA_30C);    // normal keys

    led_layer_lower_a[5] = from_rgb_color(0+27, 6,      C_CYAN_30C);
    led_layer_lower_a[6] = from_rgb_color(6+27, 1,      C_PINK_30F);
    led_layer_lower_a[8] = from_rgb_color(13+27, 1,     C_PINK_30F);
    led_layer_lower_a[7] = from_rgb_color(7+27, 6,      C_FUCHSIA_30C);      // normal keys
    led_layer_lower_a[9] = from_rgb_color(14+27, 13,    C_FUCHSIA_30C);    // normal keys
    led_layer_lower.atoms = led_layer_lower_a;
    led_layer_lower.len = 10;

    struct rgb_matrix_layer_atom * led_layer_lower_alt_a = malloc(sizeof(struct rgb_matrix_layer_atom)*10);
    led_layer_lower_alt_a[0] = from_rgb_color(0, 6,         C_ROSE_30C);        //underglow
    led_layer_lower_alt_a[1] = from_rgb_color(6, 1,         C_PINK_30F);      //alphas
    led_layer_lower_alt_a[3] = from_rgb_color(13, 1,        C_PINK_30F);      //alphas
    led_layer_lower_alt_a[2] = from_rgb_color(7, 6,         C_INDIGO_30E);      // normal keys
    led_layer_lower_alt_a[4] = from_rgb_color(14, 13,       C_INDIGO_30E);    // normal keys

    led_layer_lower_alt_a[5] = from_rgb_color(0+27, 6,      C_ROSE_30C);
    led_layer_lower_alt_a[6] = from_rgb_color(6+27, 1,      C_PINK_30F);
    led_layer_lower_alt_a[8] = from_rgb_color(13+27, 1,     C_PINK_30F);
    led_layer_lower_alt_a[7] = from_rgb_color(7+27, 6,      C_INDIGO_30E);      // normal keys
    led_layer_lower_alt_a[9] = from_rgb_color(14+27, 13,    C_INDIGO_30E);    // normal keys
    led_layer_lower_alt.atoms = led_layer_lower_alt_a;
    led_layer_lower_alt.len = 10;

    struct rgb_matrix_layer_atom * led_layer_raise_a = malloc(sizeof(struct rgb_matrix_layer_atom)*10);
    led_layer_raise_a[0] = from_rgb_color(0, 6,         C_CYAN_30C);        //underglow
    led_layer_raise_a[1] = from_rgb_color(6, 1,         C_INDIGO_30F);      //alphas
    led_layer_raise_a[3] = from_rgb_color(13, 1,        C_INDIGO_30F);      //alphas
    led_layer_raise_a[2] = from_rgb_color(7, 6,         C_EMERALD_30D);     // normal keys
    led_layer_raise_a[4] = from_rgb_color(14, 13,       C_EMERALD_30D);     // normal keys

    led_layer_raise_a[5] = from_rgb_color(0+27, 6,      C_CYAN_30C);
    led_layer_raise_a[6] = from_rgb_color(6+27, 1,      C_INDIGO_30F);
    led_layer_raise_a[8] = from_rgb_color(13+27, 1,     C_INDIGO_30F);
    led_layer_raise_a[7] = from_rgb_color(7+27, 6,      C_EMERALD_30D);      // normal keys
    led_layer_raise_a[9] = from_rgb_color(14+27, 13,    C_EMERALD_30D);    // normal keys
    led_layer_raise.atoms = led_layer_raise_a;
    led_layer_raise.len = 10;

    struct rgb_matrix_layer_atom * led_layer_raise_alt_a = malloc(sizeof(struct rgb_matrix_layer_atom)*10);
    led_layer_raise_alt_a[0] = from_rgb_color(0, 6,         C_ROSE_30C);        //underglow
    led_layer_raise_alt_a[1] = from_rgb_color(6, 1,         C_INDIGO_30F);      //alphas
    led_layer_raise_alt_a[3] = from_rgb_color(13, 1,        C_INDIGO_30F);      //alphas
    led_layer_raise_alt_a[2] = from_rgb_color(7, 6,         C_INDIGO_30D);      // normal keys
    led_layer_raise_alt_a[4] = from_rgb_color(14, 13,       C_INDIGO_30D);    // normal keys

    led_layer_raise_alt_a[5] = from_rgb_color(0+27, 6,      C_ROSE_30C);
    led_layer_raise_alt_a[6] = from_rgb_color(6+27, 1,      C_INDIGO_30F);
    led_layer_raise_alt_a[8] = from_rgb_color(13+27, 1,     C_INDIGO_30F);
    led_layer_raise_alt_a[7] = from_rgb_color(7+27, 6,      C_INDIGO_30D);      // normal keys
    led_layer_raise_alt_a[9] = from_rgb_color(14+27, 13,    C_INDIGO_30D);    // normal keys
    led_layer_raise_alt.atoms = led_layer_raise_alt_a;
    led_layer_raise_alt.len = 10;

    struct rgb_matrix_layer_atom * led_layer_adjust_a = malloc(sizeof(struct rgb_matrix_layer_atom)*24);
    led_layer_adjust_a[0] = from_rgb_color(6, 1,      C_AMBER_30F);
    led_layer_adjust_a[1] = from_rgb_color(13, 1,     C_AMBER_30F);

    led_layer_adjust_a[2] = from_rgb_color(6+27, 1,   C_AMBER_30F);
    led_layer_adjust_a[3] = from_rgb_color(13+27, 1,  C_AMBER_30F);

    led_layer_adjust_a[4] = from_rgb_color(17, 2,  C_YELLOW_30D);
    led_layer_adjust_a[5] = from_rgb_color(23, 1,  C_RED_30F); // reset eeprom
    led_layer_adjust_a[6] = from_rgb_color(24, 1,  C_RED_30F); // toggle led
    led_layer_adjust_a[7] = from_rgb_color(25, 1,  C_RED_20C); // toggle led

    led_layer_adjust_a[8]  = from_rgb_color(15, 1,  C_GREEN_30F);
    led_layer_adjust_a[9]  = from_rgb_color(16, 1,  C_TEAL_30F);
    led_layer_adjust_a[10] = from_rgb_color(20, 1,  C_GREEN_30F);
    led_layer_adjust_a[11] = from_rgb_color(19, 1,  C_TEAL_30F);
    led_layer_adjust_a[12] = from_rgb_color(21, 1,  C_GREEN_30F);
    led_layer_adjust_a[13] = from_rgb_color(22, 1,  C_TEAL_30F);

    led_layer_adjust_a[14] = from_rgb_color(26, 1,  C_NONE);

        // fn keys
        // clear rest
    led_layer_adjust_a[15] = from_rgb_color(27, 8,  C_NONE);
    led_layer_adjust_a[16] = from_rgb_color(8+27, 4,  C_AMBER_40F);
    led_layer_adjust_a[17] = from_rgb_color(39, 4,  C_NONE);
    led_layer_adjust_a[18] = from_rgb_color(16+27, 4,  C_AMBER_40F);
    led_layer_adjust_a[19] = from_rgb_color(47, 1,  C_NONE);
    led_layer_adjust_a[20] = from_rgb_color(48, 1,  C_LIME_40F);
    led_layer_adjust_a[21] = from_rgb_color(22+27, 2,  C_AMBER_40F);
    led_layer_adjust_a[22] = from_rgb_color(51, 2,  C_NONE);
    led_layer_adjust_a[23] = from_rgb_color(53, 1,  C_RED_30F);

    led_layer_adjust.atoms = led_layer_adjust_a;
    led_layer_adjust.len = 24;

    // struct rgb_matrix_layer * layers[] = {
    //     &led_layer_base,
    //     &led_layer_colmak,
    //     &led_layer_lower,
    //     &led_layer_lower_alt,
    //     &led_layer_raise,
    //     &led_layer_raise_alt,
    //     &led_layer_adjust,
    // };
    struct rgb_matrix_layer ** layers = malloc(sizeof( struct rgb_matrix_layer * ) * 7);
    layers[0] = &led_layer_base;
    layers[1] = &led_layer_colmak;
    layers[2] = &led_layer_lower;
    layers[3] = &led_layer_lower_alt;
    layers[4] = &led_layer_raise;
    layers[5] = &led_layer_raise_alt;
    layers[6] = &led_layer_adjust;

    rgb_matrix_layers.layers = layers;
    rgb_matrix_layers.len = 7;

    rgb_matrix_layers_initialized = true;
}







/** trigger the lightning layer at index <ind> in the global array */
void activate_rgb_lightning_layer(uint8_t ind, uint8_t min, uint8_t max) {
    if (ind >= rgb_matrix_layers.len){
        // failure! set all colors to red!
        rgb_matrix_set_color_all(0xa0,0x00,0x00);
        return;
    }
    struct rgb_matrix_layer rml = *rgb_matrix_layers.layers[ind];
    for (int i = 0; i<rml.len;i++){
        struct rgb_matrix_layer_atom atom = rml.atoms[i];
        for (int led = atom.ind_start;led<atom.ind_start+atom.amount; led++){
            if (led >= min && led < max) {
                rgb_matrix_set_color(led, atom.red,atom.green, atom.blue);
            }
        }
    }
}





