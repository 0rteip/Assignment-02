#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include <Arduino.h>
#include <ServoTimer2.h>

class ServoMotorImpl : public ServoMotor
{

public:
  ServoMotorImpl(int pin);

  void on();
  void off();

protected:
  void setPosition(int angle);

private:
  int pin;
  ServoTimer2 *motor;
};

#endif
