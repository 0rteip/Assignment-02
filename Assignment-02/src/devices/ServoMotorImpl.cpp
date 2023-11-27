#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin)
{
  this->pin = pin;
}

void ServoMotorImpl::on()
{
  // updated values: min is 544, max 2400 (see ServoTimer2 doc)
  motor.attach(pin); //, 544, 2400);
  Serial.println("Motor on");
}

void ServoMotorImpl::setPosition(int angle)
{
  if (angle > 180)
  {
    angle = 180;
  }
  else if (angle < 0)
  {
    angle = 0;
  }
  // 750 -> 0, 2250 -> 180
  // 750 + angle*(2250-750)/180
  // updated values: min is 544, max 2400 (see ServoTimer2 doc)
  float coeff = (2400.0 - 544.0) / 180;
  motor.write(544 + angle * coeff);

  Serial.print("Motor position: ");
  Serial.println(angle == 0     ? "CLOSED"
                 : angle == 180 ? "OPEN"
                                : String(angle));
}

void ServoMotorImpl::off()
{
  Serial.println("Motor off");
  motor.detach();
}
