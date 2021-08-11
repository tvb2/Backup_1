#ifndef RELAY_H
#define RELAY_H
class Relay{
  public:
  bool enable{true}, statusNO{false},statusNC{true};

  bool contactsNO();

  bool contactsNC();
};
#endif
