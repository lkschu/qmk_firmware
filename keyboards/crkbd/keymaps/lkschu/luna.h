#ifndef LUNA
#define LUNA

#include <stdint.h>
#include <stdbool.h>


/* timers */
// uint32_t anim_timer = 0;

/* current frame */
// uint8_t current_frame = 0;


// bool luna_is_sneaking = false;
// bool luna_is_jumping  = false;
// bool showedJump = true;



struct luna {
    bool is_barking;
    bool is_sneaking;
    bool is_jumping;

    bool _showed_jump;
    uint8_t _current_frame;
    uint8_t _current_wpm;
    uint32_t _anim_timer;
};




// static void render_luna(int LUNA_X, int LUNA_Y);
void render_luna(int LUNA_X, int LUNA_Y, struct luna * luna);



#endif
