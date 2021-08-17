#include "TimeRelayFuncA.h"
TimeRelayFuncA::TimeRelayFuncA()
{
    timeSet=0;
    elapsed=0;
    enable=0;
    status=0;
    NO=0;
    NC=0;//1 active, 0 not active

}
bool TimeRelayFuncA::ckIfDN()
{
    if (enable)
    {
        elapsed++;
        if (elapsed>=timeSet)//Relay will transfer as soon as timer is reaches preset.
        {
            status=1;
        }
      }else
      {
        elapsed=0;
        status=0;
      }
    return status;
}

bool TimeRelayFuncA::contactsNO()
{
        NO=status ? true:false;
        return NO;
}

bool TimeRelayFuncA::contactsNC()
{
        NC=status ? false:true;
        return NC;
}
