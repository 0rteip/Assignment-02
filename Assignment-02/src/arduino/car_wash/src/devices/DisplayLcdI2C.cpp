#include "DisplayLcdI2C.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

DisplayLcdI2C::DisplayLcdI2C()
{
    this->lcd = new LiquidCrystal_I2C(0x27, LCD_LENGHT, 2);
    this->lcd->init();
    this->lcd->backlight();
    this->lcd->leftToRight();

    this->lcd->createChar(0, this->zero);
    this->lcd->createChar(1, this->one);
    this->lcd->createChar(2, this->two);
    this->lcd->createChar(3, this->three);
    this->lcd->createChar(4, this->four);
    this->lcd->createChar(5, this->five);
}

void DisplayLcdI2C::on()
{
    this->lcd->backlight();
}

void DisplayLcdI2C::off()
{
    this->lcd->noBacklight();
}

void DisplayLcdI2C::clear()
{
    this->lcd->clear();
}

void DisplayLcdI2C::scroll()
{
    if (this->needScroll)
    {
        this->lcd->scrollDisplayLeft();
    }
}

void DisplayLcdI2C::display(char string[])
{
    this->clear();
    this->lcd->print(string);
    // Check id string is longer than 16 chars
    this->needScroll = strlen(string) > LCD_LENGHT;
}

void DisplayLcdI2C::updateProgress(int progress)
{
    this->clear();
    this->needScroll = false;
    this->lcd->setCursor(0, 0);
    this->lcd->print("Progress: ");
    this->lcd->print(progress);
    this->lcd->print("%");

    this->updateProgressBar(progress, 100, 1);
}

void DisplayLcdI2C::updateProgressBar(unsigned long progress, unsigned long totalCount, int lineToPrintOn)
{
    double factor = totalCount / 80.0;
    int percent = (progress + 1) / factor;
    int number = percent / 5;
    int remainder = percent % 5;
    if (number > 0)
    {
        for (int j = 0; j < number; j++)
        {
            this->lcd->setCursor(j, lineToPrintOn);
            this->lcd->write(5);
        }
    }
    this->lcd->setCursor(number, lineToPrintOn);
    this->lcd->write(remainder);
    if (number < 16) // If using a 20 character display, this should be 20!
    {
        for (int j = number + 1; j <= 16; j++) // If using a 20 character display, this should be 20!
        {
            this->lcd->setCursor(j, lineToPrintOn);
            this->lcd->write(0);
        }
    }
}