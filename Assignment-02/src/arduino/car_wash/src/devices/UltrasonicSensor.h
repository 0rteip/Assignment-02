#ifndef __ULTRASONIC_SENSOR__
#define __ULTRASONIC_SENSOR__

#include "ProximitySensor.h"
#include "NewPing.h"

#define BASE_TEMP 20

class UltrasonicSensor : public ProximitySensor
{
public:
    UltrasonicSensor(int pin);
    UltrasonicSensor(int echoPin, int trigPin);
    void setTemperature(float temp);
    float getDistance();

private:
    float temp = BASE_TEMP;
    float factor = sqrt(1 + BASE_TEMP / 273.15) / 60.368;
    NewPing *sensor;
};

#endif
