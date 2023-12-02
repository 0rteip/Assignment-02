#ifndef __CONTROL_TASK__
#define __CONTROL_TASK__

#include "kernel/Task.h"
#include "model/CarWash.h"
#include "UserConsole.h"

class ControlTask : public Task
{

public:
    ControlTask(UserConsole *userConsol, CarWash *carWash);
    void tick();

private:
    UserConsole *userConsole;
    CarWash *carWash;
};

#endif