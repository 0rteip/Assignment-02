#include "Led.h"
#include "Arduino.h"

Led::Led(int pin)
{
    this->pin = pin;
    this->isOff = true;
    pinMode(pin, OUTPUT);
}

bool Led::isOn()
{
    return !isOff;
}

void Led::switchOn()
{
    digitalWrite(pin, HIGH);
    this->isOff = false;
}

void Led::switchOff()
{
    digitalWrite(pin, LOW);
    this->isOff = true;
};
