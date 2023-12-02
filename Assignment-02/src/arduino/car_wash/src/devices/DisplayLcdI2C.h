#ifndef __DISPLAY_LCD_I2C__
#define __DISPLAY_LCD_I2C__

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define LCD_LENGHT 16

class DisplayLcdI2C
{
public:
    DisplayLcdI2C();
    void on();
    void off();
    void clear();
    void scroll();
    void display(char string[]);
    void updateProgress(int progress);

private:
    void updateProgressBar(unsigned long progress, unsigned long totalCount, int lineToPrintOn);

    LiquidCrystal_I2C *lcd;
    bool needScroll;
    byte zero[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000};
    byte one[8] = {
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000};
    byte two[8] = {
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000};
    byte three[8] = {
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100};
    byte four[8] = {
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110};
    byte five[8] = {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};
};

#endif