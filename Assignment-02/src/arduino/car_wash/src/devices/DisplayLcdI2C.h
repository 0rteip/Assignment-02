#ifndef __DISPLAY_LCD_I2C__
#define __DISPLAY_LCD_I2C__
#include <LiquidCrystal_I2C.h>
class DisplayLcdI2C { 
public:
    DisplayLcdI2C();
    void display(String string);
    void clear();
    void scroll();
    void off();
    void on();
private: 
    LiquidCrystal_I2C* lcd;
};

#endif