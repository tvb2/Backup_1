#include "TimeRelayFuncB.h"
TimeRelayFuncB::TimeRelayFuncB()
{
    trigger=0;
    timeSet=0;
    elapsed=0;
    enable=0;
    switchON=0;
    status=0;
    NO=0;
    NC=0;//1 active, 0 not active

}
bool TimeRelayFuncB::ckIfDN()
  {
    if (enable)
    {
      if (switchON && !trigger)
      {
        status=1;
        trigger=1;
      }
      if (!switchON && trigger)
      {
        if (elapsed>=timeSet)//Relay will transfer as soon as timer is reaches preset.
        {
            status=0;
            trigger=0;
        }
        elapsed++;
      }
      if (switchON && trigger)
      {
        elapsed=0;
        status=1;
      }
    }else
      {
        trigger=false;
        status=false;
      }
    return status;
  }
bool TimeRelayFuncB::contactsNO()
 {
         NO=status ? true:false;
         return NO;
 }

 bool TimeRelayFuncB::contactsNC()
 {
         NC=status ? false:true;
         return NC;
 }

