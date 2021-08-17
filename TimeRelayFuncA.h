#ifndef TIMERELAYFUNCA_H_
#define TIMERELAYFUNCA_H_
class TimeRelayFuncA{
  public:
  TimeRelayFuncA();
  int timeSet,
      elapsed;
  bool enable,status,NO,NC;//1 active, 0 not active

  bool ckIfDN();
  bool contactsNO();
  bool contactsNC();
};
#endif /* TIMERELAYFUNCA_H_ */
