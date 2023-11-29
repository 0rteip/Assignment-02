#include "DisplayLcdI2C.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

DisplayLcdI2C::DisplayLcdI2C()
{
    this->lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    this->lcd->init();
    this->lcd->backlight();
    this->lcd->leftToRight();

    this->lcd->createChar(0, zero);
    this->lcd->createChar(1, one);
    this->lcd->createChar(2, two);
    this->lcd->createChar(3, three);
    this->lcd->createChar(4, four);
    this->lcd->createChar(5, five);
}

void DisplayLcdI2C::display(String string)
{
    Serial.println(string);
    this->clear();
    lcd->print(string);
}

void DisplayLcdI2C::updateProgress(int progress)
{
    this->lcd->setCursor(0, 0);
    this->lcd->print("Progress: ");
    this->lcd->print(progress);
    this->lcd->print("%");

    Serial.print("Progress: ");
    Serial.print(progress);
    Serial.println("%");

    this->updateProgressBar(progress, 100, 1);
}

void DisplayLcdI2C::clear()
{
    this->lcd->clear();
}

void DisplayLcdI2C::scroll()
{
    this->lcd->scrollDisplayLeft();
}

void DisplayLcdI2C::off()
{
    this->lcd->noBacklight();
}

void DisplayLcdI2C::on()
{
    this->lcd->backlight();
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
            Serial.print("5");
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
            Serial.print("0");
        }
    }
}