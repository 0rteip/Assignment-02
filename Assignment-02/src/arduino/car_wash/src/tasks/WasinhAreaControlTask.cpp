#include "Arduino.h"
#include "WashingAreaControlTask.h"

WashingAreaControlTask::WashingAreaControlTask(CarWash *carWash, BlinkLedTask *blinkLedTask, ControlTask *controlTask)
    : carWash(carWash), blinkLedTask(blinkLedTask), controlTask(controlTask)
{
    this->state = IDLE;
}

void WashingAreaControlTask::tick()
{
    switch (this->state)
    {
    case IDLE:
        if (this->carWash->isCarInState() && this->carWash->getCarDistance() < MIN_DISTANCE)
        {
            setState(WAITING_ENTERING);
        }
        break;
    case WAITING_ENTERING:
        if (this->carWash->getCarDistance() > MIN_DISTANCE)
        {
            setState(IDLE);
        }
        else if (this->elapsedTimeInState() >= N2)
        {
            this->blinkLedTask->setActive(false);
            this->controlTask->setActive(true);
            this->carWash->setFullyEnteredState();
            setState(WAITING_STARTING);
        }
        break;
    case WAITING_STARTING:
        if (this->carWash->isWashingStarted())
        {
            this->elapsedTime = 0;
            this->lastTimestamp = 0;
            setState(WASHING);
        }
        break;
    case WASHING:
        if (this->carWash->isMaintenanceNeeded())
        {
            setState(MAINTENANCE);
            break;
        }

        this->elapsedTime += (this->elapsedTimeInState() - this->lastTimestamp);
        this->lastTimestamp = this->elapsedTimeInState();
        this->carWash->displayProgress(map(this->elapsedTime > N3 ? N3 : this->elapsedTime, 0, N3, 0, 100));

        if (this->elapsedTime >= N3)
        {
            this->carWash->setWashingCompletedState();
            setState(WAITING_LEAVING);
        }
        break;
    case MAINTENANCE:
        if (this->carWash->isMaintenanceComplete())
        {
            this->lastTimestamp = 0;
            setState(WASHING);
        }
        break;
    case WAITING_LEAVING:
        if (this->carWash->getCarDistance() > MAX_DISTANCE)
        {
            setState(LEAVING);
        }
        break;
    case LEAVING:
        if (this->elapsedTimeInState() >= N4)
        {
            this->blinkLedTask->setActive(false);
            this->carWash->setCarOutState();
            this->setActive(false);
            setState(IDLE);
        }
        else if (this->carWash->getCarDistance() < MAX_DISTANCE)
        {
            setState(WAITING_LEAVING);
        }
        break;
    default:
        break;
    }
}

void WashingAreaControlTask::setState(State state)
{
    this->state = state;
    this->stateTimestamp = millis();
}

long WashingAreaControlTask::elapsedTimeInState()
{
    return millis() - this->stateTimestamp;
}
