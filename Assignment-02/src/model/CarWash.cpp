#include "model/CarWash.h"
#include "config.h"
#include "devices/Led.h"
#include "devices/UltrasonicSensor.h"
#include "devices/TempSensorTMP36.h"
#include "devices/servo_motor_impl.h"
#include "kernel/Logger.h"
#include "CarWash.h"
#include <Arduino.h>

const char welcome[] = "Welcome";

CarWash::CarWash()
{
}

void CarWash::init()
{
    pir = new Pir(PIR_PIN);
    leds[0] = new Led(LED1_PIN);
    leds[1] = new Led(LED2_PIN);
    leds[2] = new Led(LED3_PIN);
    lcd = new DisplayLcdI2C();
    prox = new UltrasonicSensor(PROX_PIN);
    tempSensor = new TempSensorTMP36(TMP_PIN);
    this->washingAreaTemperture = this->tempSensor->getCelsius();
    gate = new ServoMotorImpl(GATE_PIN);
}

bool CarWash::getPrecence()
{
    this->pir->sync();
    return this->pir->isDetected();
}

void CarWash::switchL1()
{
    if (this->leds[0]->isOn())
    {
        // this->leds[0]->switchOff();
    }
    else
    {
        // this->leds[0]->switchOn();
        Serial.println("L1 Acceso");
    }
}

void CarWash::displayMessage(const char string[]) {
    lcd->clear();
    lcd->display(string);
}

void CarWash::setCarInState()
{
    this->displayMessage("Proceed to the Washing Area");
    // this->gate->setPosition
}

void CarWash::setFullyEnteredState()
{
    this->leds[1]->switchOn();
    this->gate->setPosition(GATE_CLOSE);
    this->gate->off();
    Serial.println("Car fully entered, ready to wash");
    // this->lcd->display("Ready to wash");
}

void CarWash::setWashingState()
{
    Serial.println("Washing");
    // this->lcd->display("Washing");
}

void CarWash::setWashingCompletedState()
{
    this->leds[1]->switchOff();
    this->leds[2]->switchOn();
    Serial.println("Washing completed, you can leave");
    // this->lcd->display("Washing completed");
    this->gate->on();
    this->gate->setPosition(GATE_OPEN);
}

void CarWash::setCarOutState()
{
    this->leds[2]->switchOff();
    Serial.println("Car out of the washing area");
    // this->lcd->display("Car out");
    this->gate->setPosition(GATE_CLOSE);
    this->gate->off();
}

void CarWash::scrollDisplay()
{
    this->lcd->scroll();
}

bool CarWash::isWashingStarted()
{
    Serial.println("Press button to start washing");
    // true if button has been pressed  
    delay(2000);
    return true;
}

unsigned long CarWash::getCarDistance()
{
    if (this->washingAreaTemperture != this->tempSensor->getCelsius())
    {
        this->washingAreaTemperture = this->tempSensor->getCelsius();
        this->prox->setTemperature(this->washingAreaTemperture);
    }
    return this->prox->getDistance();
}
