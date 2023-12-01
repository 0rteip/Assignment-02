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
    pir = new Pir(PIR_PIN);
    attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING);
    leds[0] = new Led(LED1_PIN);
    leds[1] = new Led(LED2_PIN);
    leds[2] = new Led(LED3_PIN);
    prox = new UltrasonicSensor(PROX_PIN);
    gate = new Gate(GATE_PIN);
    state = INACTIVE;
}

bool CarWash::getPrecence()
{
    this->pir->sync();
    return this->pir->isDetected();
}

void CarWash::setInactiveState() {
    state = INACTIVE;
    this->userConsole->sendMessage(this->getStateDescription(), this->washingAreaTemperture);
    this->userConsole->turnOffDisplay();
}

void CarWash::setCarDetectState()
{
    //Serial.println("Car detected");
    leds[0]->switchOn();
    this->userConsole->turnOnDisplay();
    this->userConsole->displayWelcome();
    state = CAR_DETECT;
}

bool CarWash::isCarDetectState()
{
    return state == CAR_DETECT;
}

bool CarWash::isFullyEnteredState()
{
    return state == FULLY_ENTERED;
}

void CarWash::setCarInState()
{
    //Serial.println("Car in");
    this->gate->open();
    this->userConsole->displayProceed();
    state = CAR_IN;
}

bool CarWash::isCarInState()
{
    return state == CAR_IN;
}

void CarWash::setFullyEnteredState()
{
    this->leds[1]->switchOn();
    this->gate->close();
    this->userConsole->displayReadyToWash();
    state = FULLY_ENTERED;
    //Serial.println("Car fully entered, ready to wash");
}

void CarWash::setWashingState()
{
    this->state = WASHING;
    this->userConsole->clear();
    //Serial.println("Washing");
}

bool CarWash::isWashingStarted()
{
    return this->state == WASHING;
}

void CarWash::setWashingCompletedState()
{
    this->leds[1]->switchOff();
    this->leds[2]->switchOn();
    this->userConsole->displayWashingCompleted();
    //Serial.println("Washing completed, you can leave");
    this->gate->open();
    this->state = WASHING_COMPLETED;
}

bool CarWash::isWashingComplete()
{
    return this->state == WASHING_COMPLETED;
}

void CarWash::setCarOutState()
{
    this->leds[2]->switchOff();
    this->userConsole->turnOffDisplay();
    //Serial.println("Car out of the washing area");
    this->gate->close();
    this->state = CAR_OUT;
}

void CarWash::setMaintenanceState()
{
    this->userConsole->displayProblem();
    //Serial.println("Maintenance started");
    this->state = MAINTENANCE;
}

bool CarWash::isMaintenanceNeeded()
{
    return this->state == MAINTENANCE;
}

bool CarWash::isMaintenanceComplete()
{
    return this->state == WASHING;
}

unsigned long CarWash::getCarDistance()
{
    return this->prox->getDistance();
}

void CarWash::setWashingAreaTemperture(float temp)
{
    this->washingAreaTemperture = temp;
    this->prox->setTemperature(this->washingAreaTemperture);
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

void CarWash::displayProgress(int progress)
{
    this->userConsole->displayProgress(progress);
}

void CarWash::scroll()
{
    this->userConsole->scroll();
}

bool CarWash::isCarOutState()
{
    return state == CAR_OUT;
}