#include "tasks/DetectTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "tasks/BlinkLedTask.h"

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
        if (carWash->getPrecence()) {
            carWash->setCarDetectState();
            setState(DETECTED);
        }
        break;
    case DETECTED: 
        if (elapsedTimeInState() >= N1 ) {
            carWash->setCarInState();
            blink->setActive(true);
            setState(CAR_IN);
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

