#include "GPIOController.h"

void GPIOController::Run() {
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
            if (numbers.back() == '#') {
                std::cout << "entered code is : ";
                numbers.pop_back();
                if ((numbers[0] == '1') and (numbers[1] == '2') and (numbers[2] == '3') and (numbers[3] == '4')) {
                    digitalWrite(26, HIGH);
                    delay(500);
                    digitalWrite(26, LOW);
//                    printFile();
                }
                for (char number: numbers)
                    std::cout << number;
                std::cout << std::endl;
                numbers.clear();
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
    pinMode(26, OUTPUT);
    for (int i = 0; i < rows_; i++) {
        pinMode(rowPins_[i], OUTPUT);
        digitalWrite(rowPins_[i], HIGH);
    }
    for (int i = 0; i < columns_; i++) {
        pinMode(columnPins_[i], INPUT);
        pullUpDnControl(columnPins_[i], PUD_UP);
    }
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