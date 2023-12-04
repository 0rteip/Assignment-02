#include "ButtonImpl.h"
#include <Arduino.h>

ButtonImpl::ButtonImpl(int pin)
{
  this->pin = pin;
  pinMode(pin, INPUT);
  sync();
}

bool ButtonImpl::isPressed()
{
  return this->pressed;
}

void ButtonImpl::sync()
{
  this->pressed = digitalRead(this->pin) == HIGH;
}
