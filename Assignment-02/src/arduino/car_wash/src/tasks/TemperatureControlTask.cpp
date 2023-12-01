#include "TemperatureControlTask.h"
#include "config.h"

#ifdef __LM35__
#include "devices/TempSensorLM35.h"
#endif

#ifdef __TMP36__
#include "devices/TempSensorTMP36.h"
#endif

TemperatureControlTask::TemperatureControlTask(CarWash *carWash, UserConsole *userConsole)
    : carWash(carWash), userConsole(userConsole)
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
    this->userConsole->sendMessage(carWash->getStateDescription(), temp);
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
        if (this->userConsole->problemIsfixed())
        {
            this->carWash->setWashingState();
            //Serial.println("Maintenance ended");
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
