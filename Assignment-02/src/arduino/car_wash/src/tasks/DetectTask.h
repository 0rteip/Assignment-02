#ifndef __DETECT_TASK__
#define __DETECT_TASK__

#include "kernel/Task.h"
#include "kernel/TaskWithReinit.h"
#include "model/CarWash.h"
#include "tasks/BlinkLedTask.h"
#include "tasks/WashingAreaControlTask.h"

class DetectTask : public Task
{

public:
  DetectTask(CarWash *carWash, WashingAreaControlTask *washingAreaControlTask , BlinkLedTask *blinkTask);
  void tick();

private:
  enum State
  {
    IDLE,
    DETECTED,
    CAR_IN
  } state;
  long stateTimestamp;

  void setState(State state);
  long elapsedTimeInState();

  CarWash *carWash;
  WashingAreaControlTask *washingAreaControlTask;
  BlinkLedTask *blink;
};

#endif