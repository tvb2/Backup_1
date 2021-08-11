#ifndef TIMERELAYFUNCA_H_
#define TIMERELAYFUNCA_H_
class TimeRelayFuncA{
  public:
  int timeSet{0},
      elapsed{0};
  bool enable{false},status{false},NO{false},NC{true};//1 active, 0 not active

  bool ckIfDN();
  bool contactsNO();
  bool contactsNC();
};
#endif /* TIMERELAYFUNCA_H_ */
