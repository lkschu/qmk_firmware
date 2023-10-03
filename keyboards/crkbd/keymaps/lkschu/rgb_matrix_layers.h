#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



#define STARTUP_HSV 0xbe,0xd1,0x99

#define POMODORO_BREAK_HSV 0x55, 0xff, 0xf0
#define POMODORO_PAUSE_HSV 0x3f, 0xf0, 0xcc
#define POMODORO_SESSION_HSV 0x00, 0xff, 0xf0


struct rgb_matrix_layer_atom {
    uint8_t ind_start;
    uint8_t amount;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct rgb_matrix_layer {
    uint8_t len;
    const struct rgb_matrix_layer_atom * atoms;
};

extern const struct rgb_matrix_layer * rgb_matrix_layers[];
extern const uint8_t rgb_matrix_layers_len;


void activate_rgb_lightning_layer(uint8_t ind, uint8_t min, uint8_t max);
