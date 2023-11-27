#include "DisplayLcdI2C.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

DisplayLcdI2C::DisplayLcdI2C() {
    this->lcd = new LiquidCrystal_I2C(0x27,16,2); 
    this->lcd->init();
    this->lcd->backlight();
    this->lcd->leftToRight();
}

void DisplayLcdI2C::display(const char string[]) {
    lcd->print(string);
}

void DisplayLcdI2C::clear() {
    this->lcd->clear();
}

void DisplayLcdI2C::scroll()
{
    this->lcd->scrollDisplayRight();
}
