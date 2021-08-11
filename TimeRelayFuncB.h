#ifndef TIMERELAYFUNCB_H_
#define TIMERELAYFUNCB_H_
class TimeRelayFuncB{
  bool trigger{false};
  public:
  int timeSet{0},
      elapsed{0};
  bool enable{false},switchON{false},status{false},NO{false},NC{true};
  bool ckIfDN();
  bool contactsNO();
  bool contactsNC();
};
#endif /* TIMERELAYFUNCB_H_ */
