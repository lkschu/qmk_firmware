#ifndef POMODORE
#define POMODORE

#include <stdint.h>
#include <stdbool.h>





enum pomodore_modes {
    POMO_RESET = -1,
    POMO_SESSION = 0,
    POMO_PAUSE = 1,
    POMO_BREAK = 2,
};


struct pomodore_instance {
    enum pomodore_modes mode;
    uint16_t sessions_until_bigbreak;
    uint16_t sessions;
    bool active;
    bool switch_session; // signals if we are ready to switch, so we don't constantly update leds
    uint16_t t;
    uint16_t min;
    const int times[];
    // int time_session;
    // int time_break_small;
    // int time_break_big;
};


void pomodore_signal(struct pomodore_instance *ins, enum pomodore_modes mode);
void pomodore_stop(struct pomodore_instance *ins);
void pomodore_cycle(struct pomodore_instance *ins);



#endif
