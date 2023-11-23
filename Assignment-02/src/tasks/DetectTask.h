#ifndef __LIGHT_CONTROL_TASK__
#define __LIGHT_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/CarWash.h"

class DetectTask: public Task {

public:
  DetectTask(CarWash* carWash); 
  void tick();

private:  

  void setState(int state);
  long elapsedTimeInState();

  enum { IDLE, DETECTED, CAR_IN} state;
  long stateTimestamp;

  CarWash* carWash;
};

#endif