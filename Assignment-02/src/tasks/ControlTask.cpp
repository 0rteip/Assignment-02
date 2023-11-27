#include "tasks/ControlTask.h"
#include "tasks/BlinkLedTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "devices/ButtonImpl.h"

ControlTask::ControlTask(int pin, BlinkLedTask* blinkTask): blink(blink){
    this->pin = pin;
    this->blink = blink;
}


void ControlTask::init() {
    this->button = new ButtonImpl(pin);
}

void ControlTask::tick(){

    if (button->isClicked() || button->isClicked()) {
        blink->setPeriod(500);
    }
}

