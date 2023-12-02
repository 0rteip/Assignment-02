#include "model/CarWash.h"
#include "config.h"
#include "devices/Led.h"
#include "devices/UltrasonicSensor.h"
#include "devices/Gate.h"
#include "kernel/Logger.h"
#include "CarWash.h"
#include <Arduino.h>

void wakeUp() {}

CarWash::CarWash(UserConsole *userConsole)
    : userConsole(userConsole)
{
    this->pir = new Pir(PIR_PIN);
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), wakeUp, RISING);
    this->leds[0] = new Led(LED1_PIN);
    this->leds[1] = new Led(LED2_PIN);
    this->leds[2] = new Led(LED3_PIN);
    this->prox = new UltrasonicSensor(PROX_PIN);
    this->gate = new Gate(GATE_PIN);
    this->swicthState(INACTIVE);
}

bool CarWash::getPrecence()
{
    this->pir->sync();
    return this->pir->isDetected();
}

unsigned long CarWash::getCarDistance()
{
    return this->prox->getDistance();
}

void CarWash::setInactiveState()
{
    this->userConsole->turnOffDisplay();
    this->swicthState(INACTIVE);
}

void CarWash::setCarDetectState()
{
    this->leds[0]->switchOn();
    this->userConsole->turnOnDisplay();
    this->userConsole->displayWelcome();
    this->swicthState(CAR_DETECT);
}

void CarWash::setCarInState()
{
    this->gate->open();
    this->userConsole->displayProceed();
    this->swicthState(CAR_IN);
}

void CarWash::setFullyEnteredState()
{
    this->leds[1]->switchOn();
    this->gate->close();
    this->userConsole->displayReadyToWash();
    this->swicthState(FULLY_ENTERED);
}

void CarWash::setWashingState()
{
    this->swicthState(WASHING);
}

void CarWash::displayProgress(int progress)
{
    this->userConsole->displayProgress(progress);
}

void CarWash::setWashingCompletedState()
{
    this->leds[1]->switchOff();
    this->leds[2]->switchOn();
    this->userConsole->displayWashingCompleted();
    this->gate->open();
    this->userConsole->sendCarsWashMessage(++this->washedCars);
    this->swicthState(WASHING_COMPLETED);
}

void CarWash::setCarOutState()
{
    this->leds[2]->switchOff();
    this->userConsole->turnOffDisplay();
    this->gate->close();
    this->swicthState(CAR_OUT);
}

void CarWash::setMaintenanceState()
{
    this->userConsole->displayProblem();
    this->swicthState(MAINTENANCE);
}

bool CarWash::isTemperatureFixed()
{
    return this->userConsole->isTemperatureFixed();
}

void CarWash::setWashingAreaTemperture(float temp)
{
    this->washingAreaTemperture = temp;
    this->prox->setTemperature(this->washingAreaTemperture);
    this->userConsole->sendTempMessage(this->washingAreaTemperture);
}

bool CarWash::isCarDetectState()
{
    return state == CAR_DETECT;
}

bool CarWash::isFullyEnteredState()
{
    return state == FULLY_ENTERED;
}

bool CarWash::isCarInState()
{
    return state == CAR_IN;
}

bool CarWash::isWashingStarted()
{
    return this->state == WASHING;
}

bool CarWash::isWashingComplete()
{
    return this->state == WASHING_COMPLETED;
}

bool CarWash::isMaintenanceNeeded()
{
    return this->state == MAINTENANCE;
}

bool CarWash::isMaintenanceComplete()
{
    return this->state == WASHING;
}

bool CarWash::isCarOutState()
{
    return state == CAR_OUT;
}

void CarWash::scroll()
{
    this->userConsole->scroll();
}

String CarWash::getStateDescription()
{
    switch (state)
    {
    case INACTIVE:
        return String("Inactive");
    case CAR_DETECT:
        return String("Car detect");
    case CAR_IN:
        return String("Car entering");
    case FULLY_ENTERED:
        return String("Car in");
    case WASHING:
        return String("Washing");
    case WASHING_COMPLETED:
        return String("Washing completed");
    case CAR_OUT:
        return String("Car out");
    case MAINTENANCE:
        return String("Maintenance");
    default:
        break;
    }
    return String();
}

void CarWash::swicthState(State s)
{
    this->state = s;
    this->userConsole->sendStatusMessage(this->getStateDescription());
}