#ifndef __BUTTON__
#define __BUTTON__

class Button
{

public:
  virtual bool isPressed() = 0;
  virtual void sync() = 0;
};

#endif
