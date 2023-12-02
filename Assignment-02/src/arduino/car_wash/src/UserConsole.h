#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__

#include "config.h"
#include "devices/Button.h"
#include "devices/DisplayLcdI2C.h"
#include <Wire.h>

#define STATUS_PREFIX String("st:")
#define TEMP_PREFIX String("tp:")
#define CARS_WASH_PREFIX String("cw:")

#define TEMP_FIXED_MESSAGE "Fixed"
class UserConsole
{

public:
  UserConsole();

  void init();
  void sync();

  void turnOnDisplay();
  void turnOffDisplay();
  void displayWelcome();
  void displayProceed();
  void displayReadyToWash();
  void displayWashing();
  void displayWashingCompleted();
  void displayProblem();
  void displayProgress(int progress);
  void scroll();

  void sendStatusMessage(String status);
  void sendTempMessage(float temp);
  void sendCarsWashMessage(int cars);

  bool isTemperatureFixed();
  bool isButtonPressed();

private:
  Button *button;
  DisplayLcdI2C *lcd;
  bool needScrol;
};

#endif
