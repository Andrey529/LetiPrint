#include "GPIOController.h"

void GPIOController::Run(std::function<int (std::string)> handler) {
    setup();
    std::string numbers;
    numbers.push_back('@');
    while (true) {
        char key = readKeypad();
        if (numbers.size() <= 5) {
            if (key == '*') {
                std::cout << "your code has been erased" << std::endl;
                numbers.clear();
            }
            if (key != '@') {
                if (numbers.back() == '@') {
                    numbers.pop_back();
                    numbers.push_back(key);
                }
            } else if (numbers.back() != '@') {
                numbers.push_back('@');
            }
            if (numbers.back() == '#' && numbers.size() == 5) {
                std::cout << "entered code is : ";
                numbers.pop_back();

                int result = handler(numbers);
                if (result == 0) {
                    std::cout << "Vse zaebis" << std::endl;
                } else if (result == -1) {
                    std::cout << "Gabella" << std::endl;
                }
                for (char number: numbers)
                    std::cout << number;
                std::cout << std::endl;
                numbers.clear();

                lcdConnector.lcdLoc(LINE1);
                lcdConnector.typeln("Privet");
                lcdConnector.lcdLoc(LINE2);
                lcdConnector.typeln("Sho ti golova");
                delay(2500);
                lcdConnector.ClrLcd();
            }
        } else {
            std::cout << "count of number is exceeded";
            numbers.clear();
            numbers.push_back('@');
        }
        delay(50);
    }
}

void GPIOController::setup() {
    wiringPiSetupGpio();
    for (int i = 0; i < rows_; i++) {
        pinMode(rowPins_[i], OUTPUT);
        digitalWrite(rowPins_[i], HIGH);
    }
    for (int i = 0; i < columns_; i++) {
        pinMode(columnPins_[i], INPUT);
        pullUpDnControl(columnPins_[i], PUD_UP);
    }
    lcdConnector.fd = wiringPiI2CSetup(I2CAddress);
    lcdConnector.lcd_init();
}

char GPIOController::readKeypad() {
    for (int row = 0; row < rows_; row++) {
        digitalWrite(rowPins_[row], LOW);
        for (int col = 0; col < columns_; col++) {
            if (digitalRead(columnPins_[col]) == LOW) {
                digitalWrite(rowPins_[row], HIGH);
                return keys_[row][col];
            }
        }
        digitalWrite(rowPins_[row], HIGH);
    }
    return '@';
}