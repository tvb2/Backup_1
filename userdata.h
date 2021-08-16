#ifndef USERDATA_H
#define USERDATA_H


class UserData
{
public:
    UserData();
    int timer_main_sec{0};
    bool controllerActive{0}, fireDetected{0};
};

#endif // USERDATA_H
