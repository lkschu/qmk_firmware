#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>




struct rgb_matrix_layer_atom {
    uint8_t ind_start;
    uint8_t amount;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct rgb_matrix_layer {
    uint8_t len;
    struct rgb_matrix_layer_atom * atoms;
};

struct rgb_matrix_layers {
    uint8_t len;
    struct rgb_matrix_layer ** layers;
};


void init_matrix_rgb_layers(void);
void activate_rgb_lightning_layer(uint8_t ind, uint8_t min, uint8_t max);
