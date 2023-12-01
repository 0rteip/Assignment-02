#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__

#include "config.h"
#include "devices/Button.h"
#include "devices/DisplayLcdI2C.h"
#include <Wire.h>

class UserConsole
{

public:
  UserConsole();

  void init();
  void sync();

  void turnOffDisplay();
  void turnOnDisplay();

  void displayWelcome();
  void displayProceed();
  void displayReadyToWash();
  void displayWashing();
  void displayWashingCompleted();
  void displayProblem();

  void sendMessage(String state, float temp);
  bool problemIsfixed();
  bool isButtonPressed();

  void displayProgress(int progress);
  void scroll();
  void clear();

private:
  Button *button;
  DisplayLcdI2C *lcd;
  bool needScrol;
};

#endif
