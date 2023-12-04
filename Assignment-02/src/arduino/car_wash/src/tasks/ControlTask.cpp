#include "Arduino.h"
#include "config.h"
#include "tasks/ControlTask.h"
#include "tasks/BlinkLedTask.h"
#include "UserConsole.h"
#include "model/CarWash.h"

ControlTask::ControlTask(BlinkLedTask *blinkLedTask, UserConsole *userConsole, CarWash *carWash)
    : blinkLedTask(blinkLedTask), userConsole(userConsole), carWash(carWash)
{
}

void ControlTask::tick()
{
    this->userConsole->sync();
    if (this->userConsole->isButtonPressed())
    {
        this->carWash->setWashingState();
        this->blinkLedTask->setPeriod(500);
        this->blinkLedTask->setActive(true);
        this->setActive(false);
    }
}
