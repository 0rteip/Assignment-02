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
    userConsole->sync();
    switch (state)
    {
    case IDLE :
        if (carWash->isFullyEnteredState()) {
            setState(WAIT_PRESS);
        }
        break;
    case WAIT_PRESS:
        if (userConsole->isButtonPressed()) {
            carWash->setWashingState();  
            setState(IDLE);
        }
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


