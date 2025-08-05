#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include QMK_KEYBOARD_H
#include "rgb_matrix_layers.h"
#include "colors.h"


/** WARN: STARTUP_HSV is defined in the header! */


/** Define your lightning layers here */


const struct rgb_matrix_layer_atom led_layer_base_a[] = {
    //{6, 4, 160,0,0} // Light 4 LEDs, starting with LED 6
    {0, 6, C_CYAN_30C},
    {0+27, 6, C_CYAN_30C},
    {6, 1, C_PURPLE_30F},
    {13, 1, C_PURPLE_30F},
    {6+27, 1, C_PURPLE_30F},
    {13+27, 1, C_PURPLE_30F},
};
const struct rgb_matrix_layer_atom led_layer_base_colemak_a[] = {
    {0, 6, C_ROSE_30C},
    {0+27, 6, C_ROSE_30C},
    {6, 1, C_PURPLE_30F},
    {13, 1, C_PURPLE_30F},
    {6+27, 1, C_PURPLE_30F},
    {13+27, 1, C_PURPLE_30F},
};
const struct rgb_matrix_layer_atom led_layer_lower_a[] = {
    {0, 6, C_CYAN_30C},
    {0+27, 6, C_CYAN_30C},
    {6, 1, C_PINK_30F},
    {13, 1, C_PINK_30F},
    {6+27, 1, C_PINK_30F},
    {13+27, 1, C_PINK_30F},
};
const struct rgb_matrix_layer_atom led_layer_lower_alt_a[] = {
    {0, 6, C_ROSE_30C},
    {0+27, 6, C_ROSE_30C},
    {6, 1, C_PINK_30F},
    {13, 1, C_PINK_30F},
    {6+27, 1, C_PINK_30F},
    {13+27, 1, C_PINK_30F},
};
const struct rgb_matrix_layer_atom led_layer_raise_a[] = {
    {0, 6, C_CYAN_30C},
    {0+27, 6, C_CYAN_30C},
    {6, 1, C_INDIGO_30F},
    {13, 1, C_INDIGO_30F},
    {6+27, 1, C_INDIGO_30F},
    {13+27, 1, C_INDIGO_30F},
};
const struct rgb_matrix_layer_atom led_layer_raise_alt_a[] = {
    {0, 6, C_ROSE_30C},
    {0+27, 6, C_PURPLE_30C},
    {6, 1, C_INDIGO_30F},
    {13, 1, C_INDIGO_30F},
    {6+27, 1, C_INDIGO_30F},
    {13+27, 1, C_INDIGO_30F},
};
const struct rgb_matrix_layer_atom led_layer_adjust_a[] = {
    {6, 1, C_AMBER_30F},
    {13, 1, C_AMBER_30F},
    {6+27, 1, C_AMBER_30F},
    {13+27, 1, C_AMBER_30F},

    {17, 2, C_YELLOW_30D},
    {23, 1, C_RED_30F}, // reset eeprom
    {24, 1, C_RED_30F}, // toggle led
    {25, 1, C_RED_20C}, // toggle led

    {15, 1, C_GREEN_30F},
    {16, 1, C_TEAL_30F},
    {20, 1, C_GREEN_30F},
    {19, 1, C_TEAL_30F},
    {21, 1, C_GREEN_30F},
    {22, 1, C_TEAL_30F},

    {26, 1, C_NONE},


    // fn keys
    // clear rest
    {27, 8, C_NONE},
    {8+27, 4, C_AMBER_40F},
    {39, 4, C_NONE},
    {16+27, 4, C_AMBER_40F},
    {47, 1, C_NONE},
    {48, 1, C_LIME_40F},
    {22+27, 2, C_AMBER_40F},
    {51, 2, C_NONE},
    {53, 1, C_RED_30F},
};












// Create arrays with associated length
const struct rgb_matrix_layer led_layer_base = {
    sizeof(led_layer_base_a)/sizeof(struct rgb_matrix_layer_atom),
    led_layer_base_a
    };
const struct rgb_matrix_layer led_layer_colmak = {
    sizeof(led_layer_base_colemak_a)/sizeof(struct rgb_matrix_layer_atom),
    led_layer_base_colemak_a
    };
const struct rgb_matrix_layer led_layer_lower = {
    sizeof(led_layer_lower_a)/sizeof(struct rgb_matrix_layer_atom),
    led_layer_lower_a
    };
const struct rgb_matrix_layer led_layer_lower_alt = {
    sizeof(led_layer_lower_alt_a)/sizeof(struct rgb_matrix_layer_atom),
    led_layer_lower_alt_a
    };
const struct rgb_matrix_layer led_layer_raise = {
    sizeof(led_layer_raise_a)/sizeof(struct rgb_matrix_layer_atom),
    led_layer_raise_a
    };
const struct rgb_matrix_layer led_layer_raise_alt = {
    sizeof(led_layer_raise_alt_a)/sizeof(struct rgb_matrix_layer_atom),
    led_layer_raise_alt_a
    };
const struct rgb_matrix_layer led_layer_adjust = {
    sizeof(led_layer_adjust_a)/sizeof(struct rgb_matrix_layer_atom),
    led_layer_adjust_a
    };
// Now define the array of layers. Later layers take precedence
const struct rgb_matrix_layer * rgb_matrix_layers[] = {
        &led_layer_base,
        &led_layer_colmak,
        &led_layer_lower,
        &led_layer_lower_alt,
        &led_layer_raise,
        &led_layer_raise_alt,
        &led_layer_adjust
        };
const uint8_t rgb_matrix_layers_len = sizeof(rgb_matrix_layers)/sizeof(rgb_matrix_layers[0]);

/** trigger the lightning layer at index <ind> in the global array */
void activate_rgb_lightning_layer(uint8_t ind, uint8_t min, uint8_t max) {
    if (ind >= rgb_matrix_layers_len){
        // failure! set all colors to red!
        rgb_matrix_set_color_all(0xa0,0x00,0x00);
        return;
    }
    struct rgb_matrix_layer rml = *rgb_matrix_layers[ind];
    for (int i = 0; i<rml.len;i++){
        struct rgb_matrix_layer_atom atom = rml.atoms[i];
        for (int led = atom.ind_start;led<atom.ind_start+atom.amount; led++){
            if (led >= min && led < max) {
                rgb_matrix_set_color(led, atom.red,atom.green, atom.blue);
            }
        }
    }
}





