#include "tasks/DetectTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "tasks/BlinkLedTask.h"
#include "tasks/DistanceControlTask.h"
#include <avr/sleep.h>

DetectTask::DetectTask(CarWash *carWash, DistanceControlTask *distanceControlTask, BlinkLedTask *blink)
    : carWash(carWash), distanceControlTask(distanceControlTask), blink(blink)
{
    this->carWash = carWash;
    this->blink = blink;
    setState(IDLE);
}

void DetectTask::tick()
{
    this->carWash->scroll();
    switch (state)
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
            carWash->setCarInState();
            blink->setActive(true);
            this->distanceControlTask->setActive(true);
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
    state = s;
    stateTimestamp = millis();
}

long DetectTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}
