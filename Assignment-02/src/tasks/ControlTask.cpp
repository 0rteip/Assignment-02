#include "tasks/ControlTask.h"
#include "tasks/BlinkLedTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "devices/ButtonImpl.h"

ControlTask::ControlTask(BlinkLedTask* blink, UserConsole* userConsole, CarWash* carWash): blink(blink), userConsole(userConsole), carWash(carWash){
    this->blink = blink;
    this->userConsole = userConsole;
    this->carWash = carWash;
    setState(IDLE);
}

void ControlTask::tick(){
    switch (state)
    {
    case IDLE :
        if (carWash->isCarDetectState()) {
            userConsole->displayWelcome();
            setState(CAR_DETECT);
        }
        break;
    case CAR_DETECT:
        if (carWash->isCarInState()) {
            userConsole->displayProceed();
            setState(CAR_IN);
        }
        break;
    case CAR_IN :
        break;
    default:
        break;
    }
}

void ControlTask::setState(State state){
    this->state = state;
    stateTimestamp = millis();
}

long ControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}


