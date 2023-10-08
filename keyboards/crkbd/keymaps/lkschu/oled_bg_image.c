#include <stdint.h>
#include "oled_bg_image.h"
#include QMK_KEYBOARD_H

void oled_render_one_of_logos(uint8_t seed) {
    uint8_t nr = seed%(sizeof(oled_bg_images)/sizeof(oled_bg_images[0]));
    oled_write_raw_P(oled_bg_images[nr].logo,oled_bg_images[nr].len);
}
