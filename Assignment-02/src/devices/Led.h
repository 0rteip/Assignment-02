#ifndef __LED__
#define __LED__

#include "Light.h"

class Led: public Light { 
public:
  Led(int pin);
  bool isOn();
  void switchOn();
  void switchOff();    
protected:
  int pin;  
  bool on;
};

#endif
