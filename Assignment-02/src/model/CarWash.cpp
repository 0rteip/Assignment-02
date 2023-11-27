#include "model/CarWash.h"
#include "config.h"
#include "devices/Led.h"
#include "devices/UltrasonicSensor.h"
#include "devices/Gate.h"
#include "kernel/Logger.h"
#include "CarWash.h"
#include <Arduino.h>

CarWash::CarWash(UserConsole *userConsole)
    : userConsole(userConsole)
{
}

void CarWash::init()
{
    pir = new Pir(PIR_PIN);
    leds[0] = new Led(LED1_PIN);
    leds[1] = new Led(LED2_PIN);
    leds[2] = new Led(LED3_PIN);
    prox = new UltrasonicSensor(PROX_PIN);
    gate = new Gate(GATE_PIN);
    state = IDLE;
}

bool CarWash::getPrecence()
{
    this->pir->sync();
    return this->pir->isDetected();
}

void CarWash::setCarDetectState()
{
    leds[0]->switchOn();
    this->userConsole->displayWelcome();
    state = CAR_DETECT;
}

bool CarWash::isCarDetectState()
{
    return state == CAR_DETECT;
}

void CarWash::setCarInState()
{
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
    Serial.println("Car fully entered, ready to wash");
}

void CarWash::setWashingState()
{
    this->userConsole->displayWashing();
    Serial.println("Washing");
}

bool CarWash::isWashingStarted()
{
    return this->leds[1]->isOn();
}

void CarWash::setWashingCompletedState()
{
    this->leds[1]->switchOff();
    this->leds[2]->switchOn();
    this->userConsole->displayWashingCompleted();
    Serial.println("Washing completed, you can leave");
    this->gate->open();
}

bool CarWash::isWashingComplete()
{
    delay(2000);
    return true;
}

void CarWash::setCarOutState()
{
    this->leds[2]->switchOff();
    this->userConsole->turnOffDisplay();
    Serial.println("Car out of the washing area");
    this->gate->close();
}

void CarWash::setMaintenanceState()
{
    this->userConsole->displayProblem();
    Serial.println("Maintenance started");
}

bool CarWash::isMaintenanceComplete()
{
    delay(2000);
    return true;
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