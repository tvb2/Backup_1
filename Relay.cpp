#include "Relay.h"
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
