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
        Serial.println("Waiting for a car to enter the washing area");
        if (this->carWash->isCarInState() && this->carWash->getCarDistance() < MIN_DISTANCE)
        {
            Serial.println("Car in the washing area");
            setState(WAITING_ENTERING);
        }
        break;
    case WAITING_ENTERING:
        Serial.print("Car distance: ");
        Serial.println(this->carWash->getCarDistance());

        if (this->carWash->getCarDistance() > MIN_DISTANCE)
        {
            Serial.println("Car out of the washing area");
            setState(IDLE);
        }
        else if (this->elapsedTimeInState() >= N2)
        {
            this->blinkLedTask->setActive(false);
            this->carWash->setFullyEnteredState();
            setState(WASHING);
        }
        
        break;
    case WASHING:
        if (this->carWash->isWashingStarted()) {
            this->carWash->displayTime(elapsedTimeInState());
            if (this->elapsedTimeInState() >= N4)
            {
                setState(WAITING_LEAVING);
            }
        }
            break;
    case WAITING_LEAVING:
        if (this->carWash->getCarDistance() > MAX_DISTANCE)
        {
            Serial.println("Car leaving the washing area");
            this->carWash->setWashingCompletedState();
            setState(LEAVING);
        }
        break;
    case LEAVING:
        if (this->carWash->getCarDistance() < MAX_DISTANCE)
        {
            Serial.println("Car back in the washing area");
            setState(WAITING_LEAVING);
        }
        else if (this->elapsedTimeInState() >= N4)
        {
            this->carWash->setCarOutState();
            setState(IDLE);
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
