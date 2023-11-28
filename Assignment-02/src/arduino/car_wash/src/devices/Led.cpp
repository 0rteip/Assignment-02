#include "Led.h"
#include "Arduino.h"

Led::Led(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
  this->on = false;
}

bool Led::isOn() {
    return on;
}

void Led::switchOn(){
    Serial.println("Accendo");
    digitalWrite(pin,HIGH);
    this->on = true;
}

void Led::switchOff(){
    digitalWrite(pin,LOW);
    this->on = false;
    Serial.println("Spengo");
};
