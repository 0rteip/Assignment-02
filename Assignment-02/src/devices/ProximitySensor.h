#ifndef __PROX_SENSOR__
#define __PROX_SENSOR__

class ProximitySensor
{

public:
  virtual unsigned long getDistance() = 0;
};

#endif
