#ifndef __WASHING_AREA_CONTROL_TASK__
#define __WASHING_AREA_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/CarWash.h"
#include "tasks/BlinkLedTask.h"
#include "tasks/ControlTask.h"

// A distance of 100 cm is the distance to consider a car is in the washing area
#define MIN_DISTANCE 8
// A distance of 500 cm is the distance to consider a car is out the washing area
#define MAX_DISTANCE 8

class WashingAreaControlTask : public Task
{

public:
    WashingAreaControlTask(CarWash *carWash, BlinkLedTask *blinkLedTask, ControlTask *controlTask);
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

    int elapsedTime;
    long lastTimestamp;
    long stateTimestamp;

    CarWash *carWash;
    BlinkLedTask *blinkLedTask;
    ControlTask *controlTask;
};

#endif
