#ifndef __GATE__
#define __GATE__

#include "ServoMotorImpl.h"

#define OPEN_ANGLE 2250
#define CLOSE_ANGLE 900

class Gate : public ServoMotorImpl
{

public:
    Gate(int pin);

    void open();
    void close();
};

#endif