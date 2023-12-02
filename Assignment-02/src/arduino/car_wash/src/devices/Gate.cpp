#include "Gate.h"

Gate::Gate(int pin) : ServoMotorImpl(pin)
{
    this->on();
    this->close();
}

void Gate::open()
{
    this->on();
    this->setPosition(OPEN_ANGLE);
}

void Gate::close()
{
    this->setPosition(CLOSE_ANGLE);
    this->off();
}
