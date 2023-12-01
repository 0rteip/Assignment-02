#include "Arduino.h"
#include "DistanceControlTask.h"

DistanceControlTask::DistanceControlTask(CarWash *carWash, BlinkLedTask *blinkLedTask)
    : carWash(carWash), blinkLedTask(blinkLedTask)
{
    this->state = IDLE;
}

void DistanceControlTask::tick()
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
        Serial.print("Car distance: ");
        Serial.println(this->carWash->getCarDistance());

        if (this->carWash->getCarDistance() > MIN_DISTANCE)
        {
            setState(IDLE);
        }
        else if (this->elapsedTimeInState() >= N2)
        {
            this->blinkLedTask->setActive(false);
            this->carWash->setFullyEnteredState();
            setState(WAITING_STARTING);
        }
        break;
    case WAITING_STARTING:
        if (this->carWash->isWashingStarted())
        {
            setState(WASHING);
        }
        break;
    case WASHING:
        this->elapsedTime = this->elapsedTimeInState();
        this->carWash->displayProgress(map(this->elapsedTime > N3 ? N3 : this->elapsedTime, 0, N3, 0, 100));

        if (this->elapsedTime >= N3)
        {
            this->carWash->setWashingCompletedState();
            setState(WAITING_LEAVING);
        }
        else if (this->carWash->isMaintenanceNeeded())
        {
            setState(MAINTENANCE);
        }
        break;
    case MAINTENANCE:
        if (this->carWash->isMaintenanceComplete())
        {
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

void DistanceControlTask::setState(State state)
{
    this->state = state;
    this->stateTimestamp = millis();
}

long DistanceControlTask::elapsedTimeInState()
{
    return millis() - this->stateTimestamp;
}
