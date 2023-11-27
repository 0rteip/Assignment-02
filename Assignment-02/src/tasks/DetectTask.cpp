#include "tasks/DetectTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "tasks/BlinkLedTask.h"

DetectTask::DetectTask(CarWash* carWash, BlinkLedTask* blink):
    carWash(carWash),blink(blink)
     {
        setState(IDLE);
}
  
void DetectTask::tick(){
    switch (state)
    {
    case IDLE:
        if (carWash->getPrecence()) {
            carWash->setCarDetectState();
            state = DETECTED;

        }
        /*if(elapsedTimeInState() > 5000) {
            blink->setPeriod(500);
            setState(CAR_IN);
        }*/


        break;
    case DETECTED: 
        if (elapsedTimeInState() >= N1 ) {
            state = CAR_IN;
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

