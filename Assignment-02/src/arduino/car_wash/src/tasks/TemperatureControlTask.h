#ifndef __TEMPERATURE_CONTROL_TASK__
#define __TEMPERATURE_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/CarWash.h"
#include "devices/TempSensor.h"

// A temperature of X degrees means there an error in the washing area
#define MAX_TEMP 23

class TemperatureControlTask : public Task
{

public:
    TemperatureControlTask(CarWash *carWash);
    void tick();

private:
    enum State
    {
        IDLE,
        HEATING,
        FIXING
    } state;

    void setState(State state);
    long elapsedTimeInState();
    void checkTemp();

    long stateTimestamp;
    float temp;

    CarWash *carWash;
    TempSensor *tempSensor;
};

#endif