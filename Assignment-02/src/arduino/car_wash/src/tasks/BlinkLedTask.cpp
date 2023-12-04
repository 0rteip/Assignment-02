#include "tasks/BlinkLedTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"

BlinkLedTask::BlinkLedTask(int pin) {
    setState(OFF);
    this->pin = pin;
}


void BlinkLedTask::init(int period) {
    Task::init(period);
    this->led = new Led(pin); 
    this->setState(OFF);
}

void BlinkLedTask::tick(){
    switch (this->state)
    {
    case OFF:
        digitalWrite(pin, HIGH);
        this->setState(ON);
        break;
    case ON :
        digitalWrite(pin, LOW);
        this->setState(OFF);
    default:
        break;
    }
}

void BlinkLedTask::setState(State s)
{
    this->state = s;
    this->stateTimestamp = millis();
}

long BlinkLedTask::elapsedTimeInState(){
    return millis() - this->stateTimestamp;
}
