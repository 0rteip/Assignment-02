#include "UserConsole.h"
#include "Arduino.h"
#include "devices/ButtonImpl.h"
#include "devices/DisplayLcdI2C.h"
#include "kernel/MsgService.h"
#include <avr/sleep.h>
#include "config.h"

UserConsole::UserConsole()
{
  this->lcd = new DisplayLcdI2C();
  this->button = new ButtonImpl(BT_PIN);
}

void UserConsole::init()
{
}

void UserConsole::sync()
{
  this->button->sync();
}

bool UserConsole::isButtonPressed()
{
  return button->isPressed();
}

void UserConsole::turnOnDisplay()
{
  this->lcd->on();
}

void UserConsole::turnOffDisplay()
{
  this->lcd->off();
}

void UserConsole::displayWelcome()
{
  this->lcd->display("Welcome");
}

void UserConsole::displayProceed()
{
  this->lcd->display("Proceed to the Washing Area");
}

void UserConsole::displayReadyToWash()
{
  this->lcd->display("Ready to Wash");
}

void UserConsole::displayWashing()
{
  this->lcd->display("Washing");
}

void UserConsole::displayWashingCompleted()
{
  this->lcd->display("Washing complete, you can leave the area");
}

void UserConsole::displayProblem()
{
  this->lcd->display("Detected a Problem - Please Wait");
}

void UserConsole::displayProgress(int progress)
{
  this->lcd->updateProgress(progress);
}

void UserConsole::scroll()
{

  this->lcd->scroll();
}

void UserConsole::sendStatusMessage(String status)
{
  MsgService.sendMsg(STATUS_PREFIX + status);
}

void UserConsole::sendTempMessage(float temp)
{
  MsgService.sendMsg(TEMP_PREFIX + temp);
}

void UserConsole::sendCarsWashMessage(int cars)
{
  MsgService.sendMsg(CARS_WASH_PREFIX + cars);
}

bool UserConsole::isTemperatureFixed()
{
  if (MsgService.isMsgAvailable() && MsgService.receiveMsg()->getContent().equals(TEMP_FIXED_MESSAGE))
  {
    return true;
  }
  return false;
}
