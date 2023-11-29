#ifndef __CAR_WASH__
#define __CAR_WASH__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/UltrasonicSensor.h"
#include "UserConsole.h"
#include "devices/Gate.h"
#include "config.h"

class CarWash
{
public:
    CarWash(UserConsole *userConsole);

    // set state
    void setCarInState();
    void setCarDetectState();
    void setFullyEnteredState();
    void setWashingState();
    void setWashingCompletedState();
    void setCarOutState();
    void setMaintenanceState();

    // get state
    bool isCarInState();
    bool isCarDetectState();
    bool isFullyEnteredState();
    bool isWashingStarted();
    bool isWashingComplete();
    bool isMaintenanceComplete();

    //sleep
    void off();
    void on();
    
    // get data
    bool getPrecence();
    unsigned long getCarDistance();
    void setWashingAreaTemperture(float temp);
    String recState();

private:
    enum State
    {
        INACTIVE,
        CAR_DETECT,
        CAR_IN,
        FULLY_ENTERED,
        WASHING,
        WASHING_COMPLETED,
        CAR_OUT,
        MAINTENANCE
    } state;

    bool detect;
    bool stateL1;
    float washingAreaTemperture;

    UserConsole *userConsole;
    Pir *pir;
    Led *leds[LED_NUM];
    Gate *gate;
    UltrasonicSensor *prox;
};

#endif