#include QMK_KEYBOARD_H
#include <stdint.h>
#include <stdbool.h>

#include "pomodore.h"
#include "config.h"



#define POMODORO_BREAK_HSV 0x55, 0xff, 0xf0
#define POMODORO_PAUSE_HSV 0x3f, 0xf0, 0xcc
#define POMODORO_SESSION_HSV 0x00, 0xff, 0xf0


void pomodore_signal(struct pomodore_instance *ins, enum pomodore_modes mode) {
    /* Signal that pomodore should switch state */
    switch (mode) {
        case POMO_SESSION:
            if (ins->sessions % ins->sessions_until_bigbreak == 0) {
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



void pomodore_stop(struct pomodore_instance *ins) {
    if (ins->active) {
        ins->t = 0;
        ins->min = 0;
        ins->active = false;
        ins->switch_session = false;
        ins->sessions = 0;
        pomodore_signal(ins, POMO_RESET);
    }

}


void pomodore_cycle(struct pomodore_instance *ins) {
    /* We have very limited state transitions:
     * Off -> SESSION
     * SESSION -> PAUSE/BREAK
     * PAUSE/BREAK -> SESSION
     * (SESSION/PAUSE/BREAK -> Off) <- stop function
     *
     * also check if we are in 'switch' state so we don't immediately start a new mode when we skip ahead
     * */
    if (!ins->active) {
        ins->t = 0;
        ins->min = 0;
        ins->active = true;
        ins->mode = POMO_SESSION;
        ins->sessions++;
        return;
    } else if (!ins->switch_session) {
        ins->switch_session = true;
        pomodore_signal(ins, ins->mode);
        return;
    }
    if (ins->mode == POMO_SESSION) {
        ins->t = 0;
        ins->min = 0;
        ins->switch_session = false;
        if (ins->sessions % ins->sessions_until_bigbreak == 0) {
            ins->mode = POMO_BREAK;
        } else {
            ins->mode = POMO_PAUSE;
        }
        pomodore_signal(ins, POMO_RESET);
        return;
    }
    if (ins->mode == POMO_BREAK || ins->mode == POMO_PAUSE) {
        ins->t = 0;
        ins->min = 0;
        ins->switch_session = false;
        ins->mode = POMO_SESSION;
        ins->sessions++;
        pomodore_signal(ins, POMO_RESET);
        return;
    }
}
