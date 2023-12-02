#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor
{

public:
  virtual void on() = 0;
  virtual void off() = 0;

protected:
  virtual void setPosition(int angle) = 0;
};

#endif
