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
        if (this->carWash->getCarDistance() < MIN_DISTANCE)
        {
            Serial.println("Car in the washing area");
            setState(MEASURING);
        }
        break;
    case MEASURING:
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
            setState(WAITING_WASHING);
        }
        break;
    case WAITING_WASHING:
        if (this->carWash->isWashingStarted())
        {
            this->carWash->setWashingState();
            setState(WASHING);
        }
        break;
    case WASHING:
        // Should this part be in the CarWash class?
        // Because it's the CarWash that should know when the washing is completed.
        // So, the CarWash should have a method like isWashingCompleted() that returns true when the washing is completed.
        if (this->elapsedTimeInState() >= N3)
        {
            this->carWash->setWashingCompletedState();
            setState(WAITING_LEAVING);
        }
        break;
    case WAITING_LEAVING:
        if (this->carWash->getCarDistance() > MAX_DISTANCE)
        {
            Serial.println("Car leaving the washing area");
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
