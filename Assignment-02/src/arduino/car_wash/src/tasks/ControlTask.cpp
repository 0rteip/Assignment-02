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
        if (this->carWash->isFullyEnteredState()) {
            setState(WAIT_PRESS);
        }
        break;
    case WAIT_PRESS:
        if (this->userConsole->isButtonPressed()) {
            this->carWash->setWashingState();
            this->blink->init(500);
            setState(IDLE);
        }
        break;
    default:
        break;
    }
}

void ControlTask::setState(State state){
    this->state = state;
    this->stateTimestamp = millis();
}

long ControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}


