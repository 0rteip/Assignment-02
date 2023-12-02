#include "tasks/ControlTask.h"
#include "tasks/BlinkLedTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "devices/ButtonImpl.h"

ControlTask::ControlTask(UserConsole *userConsole, CarWash *carWash)
    : userConsole(userConsole), carWash(carWash)
{
}

void ControlTask::tick()
{
    this->userConsole->sync();
    if (userConsole->isButtonPressed())
    {
        carWash->setWashingState();
        this->setActive(false);
    }
}
