#ifndef __CONTROL_TASK__
#define __CONTROL_TASK__
#include "kernel/TaskWithState.h"
#include "devices/Button.h"
#include "model/CarWash.h"
#include "tasks/BlinkLedTask.h"
#include "UserConsole.h"

class ControlTask: public Task {

public:
    ControlTask(BlinkLedTask* blink, UserConsole* userConsol, CarWash* carWash);
    void tick();
    
private:
    enum  State {IDLE, CAR_IN, CAR_DETECT} state;

    void setState(State state);
    long elapsedTimeInState();
    long stateTimestamp;

    BlinkLedTask* blink;
    UserConsole* userConsole;
    CarWash* carWash;
};

#endif