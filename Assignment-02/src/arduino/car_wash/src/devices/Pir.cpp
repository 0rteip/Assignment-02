#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);     
}

void Pir::calibrate(){
	delay(10000);
}
