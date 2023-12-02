#ifndef __CONTROL_TASK__
#define __CONTROL_TASK__

#include "kernel/Task.h"
#include "tasks/BlinkLedTask.h"
#include "UserConsole.h"
#include "model/CarWash.h"

class ControlTask : public Task
{

public:
    ControlTask(BlinkLedTask *blinkLedTask, UserConsole *userConsol, CarWash *carWash);
    void tick();

private:
    BlinkLedTask *blinkLedTask;
    UserConsole *userConsole;
    CarWash *carWash;
};

#endif