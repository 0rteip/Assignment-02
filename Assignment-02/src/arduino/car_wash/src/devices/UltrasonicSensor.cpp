#include "Arduino.h"
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int pin)
    : UltrasonicSensor(pin, pin)
{
}

UltrasonicSensor::UltrasonicSensor(int echoPin, int trigPin)
    : sensor(new NewPing(echoPin, trigPin))
{
}

void UltrasonicSensor::setTemperature(float temp)
{
    this->temp = temp;
    this->factor = sqrt(1 + this->temp / 273.15) / 60.368; // Speed of sound calculation based on temperature, and cm conversion.
}

float UltrasonicSensor::getDistance()
{
    return (float)sensor->ping_median() * this->factor;
}