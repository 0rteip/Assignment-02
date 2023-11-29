#include "tasks/DetectTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "tasks/BlinkLedTask.h"
#include <avr/sleep.h>

DetectTask::DetectTask(CarWash* carWash, BlinkLedTask* blink):
    carWash(carWash), blink(blink)
     {
        this->carWash = carWash;
        this->blink = blink;
        setState(IDLE); 
}

void DetectTask::tick(){
    switch (state)
    {
    case IDLE:
        Serial.println("GOING IN POWER DOWN IN 1s ...");
        
        this->carWash->off();
        Serial.flush();
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        /** The program will continue from here. **/
        Serial.println("WAKE UP");
        /* First thing to do is disable sleep. */
        sleep_disable();
        this->carWash->on();
        carWash->setCarDetectState();
        setState(DETECTED);
        /* if (carWash->getPrecence()) {
            carWash->setCarDetectState();
            setState(DETECTED);
        } */
        break;
    case DETECTED: 
        if (elapsedTimeInState() >= N1 ) {
            carWash->setCarInState();
            blink->setActive(true);
            setState(CAR_IN);
        }
        break;
    case CAR_IN:
        if (this->carWash->isCarOutState()) {
            setState(IDLE);
        }
        break;
    default:
        break;
    }
}

void DetectTask::setState(State s){
    state = s;
    stateTimestamp = millis();
}

long DetectTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

