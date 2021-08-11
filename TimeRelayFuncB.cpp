#include "TimeRelayFuncB.h"
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
        elapsed++;
        if (elapsed>=timeSet)//Relay will transfer as soon as timer is reaches preset.
        {
            status=0;
            trigger=0;
        }
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

