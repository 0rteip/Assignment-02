#ifndef __DETECT_TASK__
#define __DETECT_TASK__

#include "kernel/Task.h"
#include "kernel/TaskWithReinit.h"
#include "model/CarWash.h"
#include "tasks/BlinkLedTask.h"
#include "tasks/DistanceControlTask.h"

class DetectTask : public Task
{

public:
  DetectTask(CarWash *carWash, DistanceControlTask *distanceControlTask, BlinkLedTask *blinkTask);
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
  DistanceControlTask *distanceControlTask;
  BlinkLedTask *blink;
};

#endif