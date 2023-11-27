#include "ButtonImpl.h"
#include <Arduino.h>

ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);  
  sync();
} 
  
bool ButtonImpl::isPressed(){
  return pressed;
}

bool ButtonImpl::isClicked(){
  return clicked;
}

void ButtonImpl::sync(){
  pressed = digitalRead(pin) == HIGH;
  updateSyncTime(millis());
}
