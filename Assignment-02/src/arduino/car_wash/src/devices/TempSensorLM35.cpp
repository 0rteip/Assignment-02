#include "TempSensorLM35.h"
#include "Arduino.h"

TempSensorLM35::TempSensorLM35(int pin)
{
  // utilizzando l istruzione analogReference
  // indico al convertitore AD che deve impiegare
  // la tensione presente sul pin AREF come
  // valore di riferimento per la conversione
  analogReference(EXTERNAL);
  this->pin = pin;
}

float TempSensorLM35::getCelsius()
{
  this->valADC = 0;

  for (byte i = 0; i < NUM_SAMPLES; i++)
  {
    valADC += analogRead(this->pin);
    delayMicroseconds(100);
  }
  // eseguo la media dei valori letti
  valADC /= NUM_SAMPLES;
  // °C = (valoreADC * PrecisioneADC) / stepGradoTensione
  temp = (valADC * ADC_PRECISION) / 0.01;

  return temp;
}
