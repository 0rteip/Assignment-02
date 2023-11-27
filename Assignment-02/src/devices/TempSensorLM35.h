#ifndef __TEMP_SENSOR_LM35__
#define __TEMP_SENSOR_LM35__

#include "TempSensor.h"

#define NUM_SAMPLES 8
// `ADC/1024` (ADC = 3.3V)
#define ADC_PRECISION 0.0032

class TempSensorLM35 : public TempSensor
{
public:
  TempSensorLM35(int pin);
  float getCelsius();

private:
  int pin;
  int valADC;
  float temp;
};

#endif