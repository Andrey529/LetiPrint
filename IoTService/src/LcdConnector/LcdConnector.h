#ifndef IOTSERVICE_LCDCONNECTOR_H
#define IOTSERVICE_LCDCONNECTOR_H

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <cstdlib>
#include <cstdio>

class LcdConnector {
public:

//    Define some device constants

    int line1 = 0x80; // 1st line
    int line2 = 0xC0; // 2nd line

    int lcd_chr = 1; // Mode - Sending data
    int lcd_cmd = 0; // Mode - Sending command

    int lcd_backlight = 0x08;  // On
//    int lcd_backlight = 0x00;  // Off

    int enable = 0b00000100; // Enable bit

    LcdConnector() = default;
    ~LcdConnector() = default;

    void lcd_init(void);
    void lcd_byte(int bits, int mode);
    void lcd_toggle_enable(int bits);

    void typeInt(int i);
    void typeFloat(float myFloat);
    void lcdLoc(int line); //move cursor
    void ClrLcd(void); // clr LCD return home
    void typeln(const char *s);
    void typeChar(char val);
    int fd{};  // seen by all subroutines

};

#endif //IOTSERVICE_LCDCONNECTOR_H
