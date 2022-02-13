# CRKBD keymap

a keymap for the crkbd/Corne keyboard intended for systems using the us-international keyboard layout.

For general adwise on how to use this please visit [qmk-newbs].



## Modifying this layout

Most modification of keycodes and colors (like underglow and indicators) can be done in **keymap.c**, adding/removing animations and setting default values is mostly done in **config.h**.

 - [alloyui] features a usefull colorpicker to convert rgb into hsv, however hsv on the website is limited by 360°,100%,100% and not by 255,255,255 so this would have to be calculated manually. Hue is still a bit off most of the time so manually adjusting might be necessary.
 - [qmk-keycodes] lists all available keycodes. Note the modifiers keycodes like ``RALT(KC_5)`` which sends holding right alt and pressing 5 resulting in €.
 - [qmk-rgb-matrix] tells you everything you need to know about the rgb matrix system.

Most modification requires flashing **both** halves and possibly resetting the internal eeprom memory. In this layout you have to switch to *Adjust* layer and press the key right of 'Esc' to flush eeprom after which you should power cycle. Remember: when flashing the slave half the keymap will be mirrored.

**Pro tip:** Power cycle your keyboard by pulling the usc cable from the pc not the board since mirco usb connections are quite fragile!



If special keys are needed, like for custom functions, they can be added by modifying **keymap.c** like this:

1. Define the names of the keycodes:

```C
enum custom_keycodes {
    TEST1,
    TEST2,
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





## Links and todos for later:

 - OLED configuration
 - https://www.reddit.com/r/olkb/comments/lmtgxc/introducing_luna_the_qmk_keyboard_pet/
 - https://www.reddit.com/r/olkb/comments/80rk31/qmk_question_on_timer_accuracy_for_pomodoro/
 - https://www.reddit.com/r/olkb/comments/riddkw/problem_with_a_timer_on_qmk/
 - https://www.reddit.com/r/olkb/comments/fo6lo8/timed_key_press_using_qmk/





[//]: # (Everything after this should not be seen... References:)

   [qmk-newb]: <https://docs.qmk.fm/#/newbs>

   [alloyui]: <https://alloyui.com/examples/color-picker/hsv.html>
   [qmk-keycodes]: <https://docs.qmk.fm/#/keycodes>
   [qmk-rgb-matrix]: <https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects>

   [quantum-functions]: <https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md>
   [feature-layers]: <https://github.com/qmk/qmk_firmware/blob/master/docs/feature_layers.md>
