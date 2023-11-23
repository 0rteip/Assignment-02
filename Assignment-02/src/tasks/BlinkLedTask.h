#ifndef __BLINK_LED_TASK__
#define __BLINK_LED_TASK__
#include "kernel/Task.h"
#include "model/CarWash.h"

class BlinkLedTask: public Task {

public:
  BlinkLedTask(int pin); 
  void tick();  
  void init(int period);
  void setPeriod(unsigned long newPeriod);
private:
  enum State { OFF, ON} state;
  void setState(State state);
  long elapsedTimeInState();

  long stateTimestamp;
  int pin;
  Led* led;
  CarWash* carWash;
};

#endif