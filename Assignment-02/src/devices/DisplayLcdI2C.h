#ifndef __DISPLAY_LCD_I2C__
#define __DISPLAY_LCD_I2C__
#include <LiquidCrystal_I2C.h>
class DisplayLcdI2C { 
public:
    DisplayLcdI2C();
    void display(char string[]);
    void clear();
    void scroll();
private: 
    LiquidCrystal_I2C* lcd;
};

#endif