#ifndef __DISTANCE_CONTROL_TASK__
#define __DISTANCE_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/CarWash.h"
#include "tasks/BlinkLedTask.h"

// A distance of 100 cm is the distance to consider a car is in the washing area
#define MIN_DISTANCE 100
// A distance of 500 cm is the distance to consider a car is out the washing area
#define MAX_DISTANCE 500

class DistanceControlTask : public Task
{

public:
    DistanceControlTask(CarWash *carWash, BlinkLedTask *blinkLedTask);
    void tick();

private:
    enum State
    {
        IDLE,
        WAITING_ENTERING,
        WASHING,
        WAITING_LEAVING,
        LEAVING
    } state;

    void setState(State state);
    long elapsedTimeInState();

    float distance;
    long stateTimestamp;
    CarWash *carWash;
    BlinkLedTask *blinkLedTask;
};

#endif
