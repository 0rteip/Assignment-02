#include "UserConsole.h"
#include "Arduino.h"
#include "devices/ButtonImpl.h"
#include "devices/DisplayLcdI2C.h"
#include "kernel/MsgService.h"
#include <avr/sleep.h>
#include "config.h"
#include "kernel/Logger.h"

UserConsole::UserConsole()
{
  this->lcd = new DisplayLcdI2C();
  this->button = new ButtonImpl(BT_PIN);
  this->needScrol = false;
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

void UserConsole::displayWelcome()
{
  this->lcd->display("Welcome");
  this->needScrol = false;
}

void UserConsole::displayProceed()
{
  this->lcd->display("Proceed to the Washing Area");
  this->needScrol = true;
}

void UserConsole::displayReadyToWash()
{
  this->lcd->display("Ready to Wash");
  this->needScrol = false;
}

void UserConsole::displayWashing()
{
  this->lcd->display("Washing");
  this->needScrol = false;
}

void UserConsole::displayWashingCompleted()
{
  this->lcd->display("Washing complete, you can leave the area");
  this->needScrol = false;
}

void UserConsole::displayProblem()
{
  this->lcd->display("Detected a Problem - Please Wait");
  this->needScrol = false;
}

void UserConsole::turnOnDisplay()
{
  this->lcd->on();
}

void UserConsole::turnOffDisplay()
{
  this->lcd->off();
}

void UserConsole::sendMessage(String state, float temp)
{
  MsgService.sendMsg("st:" + state + ":tp:" + String(temp));
}

bool UserConsole::problemIsfixed()
{
  if (MsgService.isMsgAvailable())
  {
    Msg *msg = MsgService.receiveMsg();
    if (msg->getContent().equals("Fixed"))
    {
      return true;
    }
  }
  return false;
}
