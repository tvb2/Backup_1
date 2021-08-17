#ifndef RELAY_H
#define RELAY_H
class Relay{
  public:
  Relay();
  bool enable, statusNO,statusNC;

  bool contactsNO();

  bool contactsNC();
};
#endif
