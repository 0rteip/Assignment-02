#ifndef __CAR_WASH__
#define __CAR_WASH__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/UltrasonicSensor.h"
#include "devices/TempSensor.h"
#include "devices/DisplayLcdI2C.h"
#include "devices/servo_motor.h"
#include "config.h"

#define GATE_CLOSE 0
#define GATE_OPEN 180

class CarWash
{
public:
    CarWash();
    void init();
    bool getPrecence();
    void switchL1();
    void displayMessage(const char string[]);
    void setCarInState();
    void setFullyEnteredState();
    void setWashingState();
    void setWashingCompletedState();
    void setCarOutState();
    bool isWashingStarted();
    void scrollDisplay();
    void setCarDetectState();
    unsigned long getCarDistance();

private:
    bool detect;
    bool stateL1;
    float washingAreaTemperture;
    Pir *pir;
    Led *leds[LED_NUM];
    DisplayLcdI2C *lcd;
    ServoMotor *gate;
    UltrasonicSensor *prox;
    TempSensor *tempSensor;
};

#endif