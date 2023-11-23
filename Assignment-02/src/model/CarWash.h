#ifndef __BRIDGE__
#define __BRIDGE__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"

class CarWash {
    
public: 
    CarWash();
    void init();
    
   
};


#endif