#include "Relay.h"
Relay::Relay()
{
    enable=0;
    statusNO=0;
    statusNC=0;//1 active, 0 not active
}

bool Relay::contactsNO(){
       if (enable){
       statusNO=true;
       }else{
        statusNO=false;
       }
    return statusNO;
  }

  bool Relay::contactsNC(){
    if (enable){
      statusNC=false;
    }else{
      statusNC=true;
    }
    return statusNC;
  }
