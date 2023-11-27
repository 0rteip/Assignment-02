#ifndef __BLINK_LED_TASK__
#define __BLINK_LED_TASK__
#include "kernel/TaskWithReinit.h"
#include "model/CarWash.h"

class BlinkLedTask: public TaskWithReinit{

public:
  BlinkLedTask(int pin); 
  void tick();  
  void init(int period);
  
private:
  enum State { OFF, ON} state;
  void setState(State state);
  long elapsedTimeInState();

  long stateTimestamp;
  int pin;
  Led* led;
};

#endif