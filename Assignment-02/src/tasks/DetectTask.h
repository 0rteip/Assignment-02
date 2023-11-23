#ifndef __LIGHT_CONTROL_TASK__
#define __LIGHT_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/CarWash.h"
#include "tasks/BlinkLedTask.h"
class DetectTask: public Task {

public:
  DetectTask(CarWash* carWash, BlinkLedTask* blinkTask); 
  void tick();

private:  

  enum State { IDLE, DETECTED, CAR_IN} state;
  void setState(State state);
  long elapsedTimeInState();

  long stateTimestamp;

  CarWash* carWash;
  BlinkLedTask* blink;
};

#endif