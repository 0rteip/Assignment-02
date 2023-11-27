#ifndef __TEMP_SENSOR_TMP36__
#define __TEMP_SENSOR_TMP36__

#include "TempSensor.h"

#define NUM_SAMPLES 8
// `ADC/1024` (ADC = 3.3V)
#define ADC_PRECISION 0.0032

class TempSensorTMP36 : public TempSensor
{
public:
    TempSensorTMP36(int pin);
    float getCelsius();

private:
    int pin;
    int valADC;
    float temp;
};

#endif