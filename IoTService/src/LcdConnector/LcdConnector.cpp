#include "LcdConnector.h"

void LcdConnector::lcd_init(void) {
    // Initialise display
    lcd_byte(0x33, lcd_cmd); // Initialise
    lcd_byte(0x32, lcd_cmd); // Initialise
    lcd_byte(0x06, lcd_cmd); // Cursor move direction
    lcd_byte(0x0C, lcd_cmd); // 0x0F On, Blink Off
    lcd_byte(0x28, lcd_cmd); // Data length, number of lines, font size
    lcd_byte(0x01, lcd_cmd); // Clear display
    delayMicroseconds(500);
}

void LcdConnector::lcd_byte(int bits, int mode) {

    //Send byte to data pins
    // bits = the data
    // mode = 1 for data, 0 for command
    int bits_high;
    int bits_low;
    // uses the two half byte writes to LCD
    bits_high = mode | (bits & 0xF0) | lcd_backlight ;
    bits_low = mode | ((bits << 4) & 0xF0) | lcd_backlight ;

    // High bits
    wiringPiI2CReadReg8(fd, bits_high);
    lcd_toggle_enable(bits_high);

    // Low bits
    wiringPiI2CReadReg8(fd, bits_low);
    lcd_toggle_enable(bits_low);
}

void LcdConnector::lcd_toggle_enable(int bits) {
    // Toggle enable pin on LCD display
    delayMicroseconds(500);
    wiringPiI2CReadReg8(fd, (bits | enable));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(fd, (bits & ~enable));
    delayMicroseconds(500);
}

void LcdConnector::typeInt(int i) {
    char array1[20];
    sprintf(array1, "%d",  i);
    typeln(array1);
}

void LcdConnector::typeFloat(float myFloat) {
    char buffer[20];
    sprintf(buffer, "%4.2f",  myFloat);
    typeln(buffer);
}

void LcdConnector::lcdLoc(int line) {
    lcd_byte(line, lcd_cmd);
}

void LcdConnector::ClrLcd(void) {
    lcd_byte(0x01, lcd_cmd);
    lcd_byte(0x02, lcd_cmd);
}

void LcdConnector::typeln(const char *s) {
    while ( *s ) lcd_byte(*(s++), lcd_chr);
}

void LcdConnector::typeChar(char val) {
    lcd_byte(val, lcd_chr);
}
