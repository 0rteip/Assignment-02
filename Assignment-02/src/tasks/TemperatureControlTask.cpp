#include "TemperatureControlTask.h"
#include "devices/TempSensorTMP36.h"

TemperatureControlTask::TemperatureControlTask(CarWash *carWash)
    : carWash(carWash)
{
    this->state = IDLE;
}

void TemperatureControlTask::tick()
{
    this->checkTemp();
    switch (this->state)
    {
    case IDLE:
        if (this->temp > MAX_TEMP && this->carWash->isWashingStarted())
        {
            setState(HEATING);
        }
        break;
    case HEATING:
        if (this->temp < MAX_TEMP)
        {
            setState(IDLE);
        }
        else if (this->elapsedTimeInState() >= N4)
        {
            this->carWash->setMaintenanceState();
            setState(FIXING);
        }
        break;
    case FIXING:
        if (this->carWash->isMaintenanceComplete())
        {
            Serial.println("Maintenance ended");
            setState(IDLE);
        }
        break;
    }
}

void TemperatureControlTask::setState(State state)
{
    this->state = state;
    this->stateTimestamp = millis();
}

long TemperatureControlTask::elapsedTimeInState()
{
    return millis() - this->stateTimestamp;
}

void TemperatureControlTask::checkTemp()
{
    float tmp = this->tempSensor->getCelsius();
    if (this->temp != tmp)
    {
        this->temp = tmp;
        this->carWash->setWashingAreaTemperture(this->temp);
    }
}
