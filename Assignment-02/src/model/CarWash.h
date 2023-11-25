#ifndef __CAR_WASH__
#define __CAR_WASH__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/ProximitySensor.h"
#include "devices/DisplayLcdI2C.h"
#include "devices/servo_motor.h"
#include "config.h"
class CarWash {
    
public: 
    CarWash();
    void init();
    bool getPrecence();
    void switchL1();
    void displayMessage(char string[]);
    void setCarInState();
    void scrollDisplay();
    unsigned long getCarDistance();
    
private:
    bool detect;
    bool stateL1;
    Pir* pir;
    Led* leds[LED_NUM];
    DisplayLcdI2C* lcd;
    ServoMotor* gate;
    ProximitySensor* prox;
};


#endif