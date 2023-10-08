MOUSEKEY_ENABLE = no    # Mouse keys, lets save memory
RGBLIGHT_ENABLE = no   # Enable WS2812 RGB underlight. .. actually don't, we use matrix
RGB_MATRIX_ENABLE = yes  # Matrix driver is set by default.
OLED_ENABLE     = yes
WPM_ENABLE = yes
#OLED_DRIVER     = SSD1306
LTO_ENABLE      = no  # link time optimization => smaller hex file

# not sure if this should be used https://docs.splitkb.com/hc/en-us/articles/5799904122012-Onboard-RGB
#WS2812_DRIVER = vendor


SRC += rgb_matrix_layers.c \
	   oled_bg_image.c
