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
  lcd = new DisplayLcdI2C();
  button = new ButtonImpl(BT_PIN);
  needScrol = false;
}

void UserConsole::init()
{
}

void UserConsole::sync()
{
  button->sync();
}

bool UserConsole::isButtonPressed()
{
  return button->isPressed();
}

void UserConsole::displayWelcome()
{
  lcd->display("Welcome");
  needScrol = false;
}

void UserConsole::displayProceed()
{
  lcd->display("Proceed to the Washing Area");
  needScrol = true;
}

void UserConsole::displayReadyToWash()
{
  lcd->display("Ready to Wash");
  needScrol = false;
}

void UserConsole::displayWashing()
{
  lcd->display("Washing");
  needScrol = false;
}

void UserConsole::displayWashingCompleted()
{
  lcd->display("Washing complete, you can leave the area");
  needScrol = false;
}

void UserConsole::displayProblem()
{
  lcd->display("Detected a Problem - Please Wait");
  needScrol = false;
}

void UserConsole::turnOnDisplay()
{
}

void UserConsole::turnOffDisplay()
{
}

void UserConsole::sendMessage(String state, float temp)
{
  MsgService.sendMsg("st:" + state + ":tp:" + String(temp));
}
