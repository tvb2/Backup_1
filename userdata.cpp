#include "userdata.h"
//data taken from GUI (time relay settings, status of checkboxes etc)
//initializing
    int UserData::timer_main_sec{0};
    int UserData::roll_down_timer_sec{0};
    int UserData::post_lube_cont_sec{0};
    int UserData::post_lube_on_cycle{0};
    int UserData::post_lube_off_cycle{0};
    int UserData::header_press_high_sec{0};
    bool UserData::controllerActive{0};
    bool UserData::fireDetected{0};
    bool UserData::ps3200{0};

