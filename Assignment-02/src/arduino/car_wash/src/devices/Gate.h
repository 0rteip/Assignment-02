#ifndef __GATE__
#define __GATE__

#include "ServoMotorImpl.h"

#define OPEN_ANGLE 180
#define CLOSE_ANGLE 0

class Gate : public ServoMotorImpl
{

public:
    Gate(int pin);

    void open();
    void close();
};

#endif