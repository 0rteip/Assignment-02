#ifndef __TEMPERATURE_CONTROL_TASK__
#define __TEMPERATURE_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/CarWash.h"
#include "devices/TempSensor.h"

// A temperature of X degrees means there an error in the washing area
#define MAX_TEMP 20

class TemperatureControlTask : public Task
{

public:
    TemperatureControlTask(CarWash *carWash, UserConsole *userConsole);
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
    UserConsole *userConsole;
    TempSensor *tempSensor;
};

#endif