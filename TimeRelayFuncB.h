#ifndef TIMERELAYFUNCB_H_
#define TIMERELAYFUNCB_H_
class TimeRelayFuncB{
  bool trigger;
  public:
  TimeRelayFuncB();
  int timeSet,
      elapsed;
  bool enable,switchON,status,NO,NC;
  bool ckIfDN();
  bool contactsNO();
  bool contactsNC();
};
#endif /* TIMERELAYFUNCB_H_ */
