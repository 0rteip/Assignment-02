#include "tasks/DetectTask.h"
#include "Arduino.h"
#include "config.h"
#include "tasks/BlinkLedTask.h"
#include "tasks/WashingAreaControlTask.h"
#include <avr/sleep.h>

DetectTask::DetectTask(CarWash *carWash, WashingAreaControlTask *washingAreaControlTask, BlinkLedTask *blink)
    : carWash(carWash), washingAreaControlTask(washingAreaControlTask), blink(blink)
{
    setState(IDLE);
}

void DetectTask::tick()
{
    this->carWash->scroll();
    switch (this->state)
    {
    case IDLE:
        this->carWash->setInactiveState();
        delay(1000);
        Serial.flush();
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        sleep_disable();
        this->carWash->setCarDetectState();
        setState(DETECTED);
        break;
    case DETECTED:
        if (elapsedTimeInState() >= N1)
        {
            this->carWash->setCarInState();
            this->blink->setPeriod(300);
            this->blink->setActive(true);
            this->washingAreaControlTask->setActive(true);
            setState(CAR_IN);
        }
        break;
    case CAR_IN:
        if (this->carWash->isCarOutState())
        {
            setState(IDLE);
        }
        break;
    default:
        break;
    }
}

void DetectTask::setState(State s)
{
    this->state = s;
    this->stateTimestamp = millis();
}

long DetectTask::elapsedTimeInState()
{
    return millis() - this->stateTimestamp;
}
