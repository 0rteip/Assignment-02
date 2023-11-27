#include "Gate.h"

Gate::Gate(int pin) : ServoMotorImpl(pin)
{
}

void Gate::open()
{
    this->on();
    this->setPosition(OPEN_ANGLE);
}

void Gate::close()
{
    this->on();
    this->setPosition(CLOSE_ANGLE);
}
