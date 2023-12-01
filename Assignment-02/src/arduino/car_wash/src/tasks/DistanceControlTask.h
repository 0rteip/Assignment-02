#ifndef __DISTANCE_CONTROL_TASK__
#define __DISTANCE_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/CarWash.h"
#include "tasks/BlinkLedTask.h"

// A distance of 100 cm is the distance to consider a car is in the washing area
#define MIN_DISTANCE 8
// A distance of 500 cm is the distance to consider a car is out the washing area
#define MAX_DISTANCE 8

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
        WAITING_STARTING,
        WASHING,
        MAINTENANCE,
        WAITING_LEAVING,
        LEAVING
    } state;

    void setState(State state);
    long elapsedTimeInState();

    int elapsedTime =0;
    long stateTimestamp;

    CarWash *carWash;
    BlinkLedTask *blinkLedTask;
};

#endif
