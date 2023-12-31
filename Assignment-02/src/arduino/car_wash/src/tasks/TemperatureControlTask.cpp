#include "TemperatureControlTask.h"
#include "config.h"

#ifdef __LM35__
#include "devices/TempSensorLM35.h"
#endif

#ifdef __TMP36__
#include "devices/TempSensorTMP36.h"
#endif

TemperatureControlTask::TemperatureControlTask(CarWash *carWash)
    : carWash(carWash)
{
#ifdef __TMP36__
    this->tempSensor = new TempSensorTMP36(TEMP_PIN);
#endif

#ifdef __LM35__
    this->tempSensor = new TempSensorLM35(TEMP_PIN);
#endif

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
        if (this->carWash->isWashingComplete() || this->temp < MAX_TEMP)
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
        if (this->carWash->isTemperatureFixed())
        {
            this->carWash->setWashingState();
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
