#ifndef __CONTROL_TASK__
#define __CONTROL_TASK__
#include "kernel/TaskWithState.h"
#include "devices/Button.h"
#include "model/CarWash.h"
#include "tasks/BlinkLedTask.h"

class ControlTask: public Task {

public:
    ControlTask(int pin, BlinkLedTask* blinkTask);
    void init();
    void tick();
private:

    int pin;
    BlinkLedTask* blink;
    Button* button;
};

#endif