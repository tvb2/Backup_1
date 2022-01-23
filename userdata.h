#ifndef USERDATA_H
#define USERDATA_H


class UserData
{
public:
    static int timer_main_sec;
    static int roll_down_timer_sec;
    static int post_lube_cont_sec;
    static int post_lube_on_cycle;
    static int post_lube_off_cycle;
    static int header_press_high_sec;
    static bool controllerActive;
    static bool fireDetected;
    static bool ps3200;
};

#endif // USERDATA_H
