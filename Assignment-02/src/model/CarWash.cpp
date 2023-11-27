#include "model/CarWash.h"
#include "config.h"
#include "devices/Led.h"
#include "kernel/Logger.h"
#include "CarWash.h"
#include <Arduino.h>
#define MAX_DISTANCE_FROM_RIVER 3.00

const char welcome[] = "Welcome";

CarWash::CarWash(){
}

void CarWash::init(){
    pir = new Pir(PIR_PIN);
    leds[0] = new Led(LED1_PIN);
    leds[1] = new Led(LED2_PIN);
    leds[2] = new Led(LED3_PIN);
    lcd = new DisplayLcdI2C();
    //gate = new ServoMotor();
}

bool CarWash::getPrecence() {
    this->pir->sync();
    return this->pir->isDetected();
}

void CarWash::switchL1() {
    if (this->leds[0]->isOn()) {
        //this->leds[0]->switchOff();
    } else {
        // this->leds[0]->switchOn();
        Serial.println("L1 Acceso");
    }
}

void CarWash::displayMessage(const char string[]) {
    lcd->clear();
    lcd->display(string);
}

void CarWash::setCarDetectState() {
    this->switchL1();
    this->displayMessage(welcome);
}

void CarWash::setCarInState() {
    this->displayMessage("Proceed to the Washing Area");
    //this->gate->setPosition();
}

void CarWash::scrollDisplay()
{
    this->lcd->scroll();
}

