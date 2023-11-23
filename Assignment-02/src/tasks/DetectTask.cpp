#include "tasks/DetectTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "tasks/BlinkLedTask.h"
#define DELAY_BEFORE_OFF 1000

const char welcome[] = "Welcome";

DetectTask::DetectTask(CarWash* carWash, BlinkLedTask* blink):
    blink(blink),
    carWash(carWash) {
    setState(IDLE);
}
  
void DetectTask::tick(){
    switch (state)
    {
    case IDLE:
        if (carWash->getPrecence()) {
            carWash->switchL1();
            carWash->displayMessage(welcome);
            state = DETECTED;
        }
        break;
    case DETECTED: 
        if (elapsedTimeInState() >= N1 ) {
            state = CAR_IN;
            Serial.println("Attivo il blink");
            carWash->setCarInState();
            blink->setActive(true);
        }
        break;
    case CAR_IN:
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

