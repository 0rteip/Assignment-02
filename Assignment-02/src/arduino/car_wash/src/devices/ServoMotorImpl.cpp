#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin)
{
  this->pin = pin;
  pinMode(pin, OUTPUT);
  this->motor = new ServoTimer2();
}

void ServoMotorImpl::on()
{
  motor->attach(pin);
}

void ServoMotorImpl::setPosition(int angle)
{
  // if (angle > 180)
  // {
  //   angle = 180;
  // }
  // else if (angle < 0)
  // {
  //   angle = 0;
  // }
  // 750 -> 0, 2250 -> 180
  // 750 + angle*(2250-750)/180
  // updated values: min is 544, max 2400 (see ServoTimer2 doc)
  // // float coeff = (2255.0 - 584.0) / 180;
  // Serial.print("Motor position: ");
  // Serial.println(map(angle, 750, 2250, 0, 180));

  motor->write(angle);
  delay(900);

  /* Serial.print("Motor position: ");
  Serial.println(angle == 0     ? "CLOSED"
                 : angle == 180 ? "OPEN"
                                : String(angle)); */
}

void ServoMotorImpl::off()
{
  motor->detach();
}
