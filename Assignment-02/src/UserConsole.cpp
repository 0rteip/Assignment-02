#include "UserConsole.h"
#include "Arduino.h"
#include "devices/ButtonImpl.h"
#include "devices/DisplayLcdI2C.h"
#include "kernel/MsgService.h"
#include <avr/sleep.h>
#include "config.h"
#include "kernel/Logger.h"

UserConsole::UserConsole(){
  lcd = new  DisplayLcdI2C();
  button = new ButtonImpl(BT_PIN);
  needScrol=false;
}

void UserConsole::init(){
}

void UserConsole::sync(){
  button->sync();
}

bool UserConsole::isButtonPressed() {
    return button->isPressed();
}

void UserConsole::displayWelcome() {
    lcd->clear();
    lcd->display("Welcome");
    needScrol = false;
}

void UserConsole::displayProced() {
    lcd->clear();
    lcd->display("Proceed to the Washing Area");
    needScrol = true;
}

void UserConsole::turnOnDisplay(){
}

void UserConsole::turnOffDisplay(){
}