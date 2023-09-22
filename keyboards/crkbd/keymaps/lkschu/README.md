# CRKBD keymap


A keymap for the crkbd/Corne keyboard intended for systems using the us-international keyboard layout.


For general adwise on how to use this please visit [qmk-newbs].


> :warning: I switched to the elite pi with the the RP2040 as micro controller, when compiling for Atmega32u4 the filesize might be too large!
> ```bash
> qmk compile -kb crkbd -km lkschu -e CONVERT_TO=elite_pi
> ```


# Modifying this keymap

Lightning layers for the RGB_LIGHT system are not compatible with RGB_MATRIX.
A similar feature for RGB_MATRIX is implemented in `rgb_matrix_layers.c`.

Most normal modification of keycodes can be done in **keymap.c**, while adding/removing animations and setting default values is mostly done in **config.h**.

 - [qmk-keycodes] lists all available keycodes. Note the modifiers keycodes like ``RALT(KC_5)`` which sends holding right alt and pressing 5 resulting in € (on a us intl layout).
 - [qmk-rgb-matrix] tells you everything you need to know about the rgb matrix system.

Most modification requires flashing **both** halves and possibly resetting the internal eeprom memory. In this layout you have to switch to *Adjust* layer and press the key right of 'Esc' to flush eeprom after which you should power cycle. Remember: when flashing the slave half the keymap will be mirrored.

**Pro tip:** Power cycle your keyboard by pulling the usc cable from the pc not the board since mirco usb connections are quite fragile!



If special keys are needed, like for custom functions, they can be added by modifying **keymap.c** like this:

1. Define the names of the keycodes:

```C
enum custom_keycodes {
    RESET_COLOR,
    EURO,
};
```

2. Then handle them at the end in ``process_record_user()`` like this:

```C
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* This function gets called before the actual handling is done!
     * Return true if normal handling should continue, else return false */
    switch (keycode) {
        case TEST1:
            return false; // do nothing here
            break;

        case EURO:
            if (record->event.pressed) {
                //on pressed key
                SEND_STRING("str");
            } else {
                //on release
                SEND_STRING("release");
            }
            return false; //replace this char
            break;

        default:
            if (record->event.pressed) {
                set_keylog(keycode, record);
            }
            return true; //let qmk handle the keycode
            break;
    }
}
```





## Expanding this layout

 - [quantum-functions] describes many usefull functions which are getting called on startup, sleep, wakeup, etc.
 - [feature-layers] explain which special layer functionallity can be used. LED matrix is defined in [this file](https://github.com/lkschu/qmk_firmware/blob/master/keyboards/crkbd/rev1/rev1.c).\
First it defines the mapping key&harr;led (these don't have to be all leds!). Then it defines a list of coordinates, each corresponding to 1 led (these are all leds). Then it defines a list of flags, which declare the role of the given led(by index) like normal=4,underglow=2 or modifiers=1.
 - [rgblight](https://docs.qmk.fm/#/feature_rgblight) this might also be usefull since rgb-matrix documentation is missing a few basic details, however ``RGBLIGHT`` and ``RGBMATRIX`` are two different systems!





[//]: # (Everything after this should not be seen... References:)

   [qmk-newbs]: <https://docs.qmk.fm/#/newbs>

   [alloyui]: <https://alloyui.com/examples/color-picker/hsv.html>
   [qmk-keycodes]: <https://docs.qmk.fm/#/keycodes>
   [qmk-rgb-matrix]: <https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects>

   [quantum-functions]: <https://docs.qmk.fm/#/custom_quantum_functions>
   [feature-layers]: <https://docs.qmk.fm/#/feature_layers>
