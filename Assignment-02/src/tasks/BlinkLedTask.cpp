#include "tasks/BlinkLedTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "BlinkLedTask.h"
#define DELAY_BEFORE_OFF 1000

BlinkLedTask::BlinkLedTask(int pin) {
    setState(OFF);
    this->pin = pin;
}


void BlinkLedTask::init(int period) {
    Task::init(period);
    this->led = new Led(pin); 
    state = OFF;
}

void BlinkLedTask::tick(){
    switch (state)
    {
    case OFF:
        digitalWrite(pin, HIGH);
        state = ON;
        break;
    case ON :
        digitalWrite(pin, LOW);
        state = OFF;
    default:
        break;
    }
}
void BlinkLedTask::setState(State s)
{
    state = s;
    stateTimestamp = millis();
}

long BlinkLedTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

void BlinkLedTask::setPeriod(unsigned long newPeriod) {
    myPeriod = newPeriod;
}

