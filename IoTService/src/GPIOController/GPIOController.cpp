#include "GPIOController.h"

void GPIOController::Run(std::function<int (std::string)> handler) {
    setup();
    std::string numbers;
    numbers.push_back('@');

    lcdConnector.ClrLcd();
    std::string message = "Enter your code:";
    lcdConnector.lcdLoc(lcdConnector.line1);
    lcdConnector.typeln(message.c_str());


    while (true) {
        char key = readKeypad();
        if (numbers.size() <= 5) {
            if (key == '*') {
                std::cout << "your code has been erased" << std::endl;
                numbers.clear();

                lcdConnector.ClrLcd();
                message = "Code erased";
                lcdConnector.lcdLoc(lcdConnector.line1);
                lcdConnector.typeln(message.c_str());
                delay(1000);
                continue;
            }
            if (key != '@') {
                if (numbers.back() == '@') {
                    numbers.pop_back();
                    numbers.push_back(key);

                    lcdConnector.ClrLcd();
                    message = "Enter your code:";
                    lcdConnector.lcdLoc(lcdConnector.line1);
                    lcdConnector.typeln(message.c_str());
                    lcdConnector.lcdLoc(lcdConnector.line2);
                    lcdConnector.typeln(numbers.substr(0, numbers.size() - 1).c_str());
                }
            } else if (numbers.back() != '@') {
                numbers.push_back('@');

                lcdConnector.ClrLcd();
                message = "Enter your code:";
                lcdConnector.lcdLoc(lcdConnector.line1);
                lcdConnector.typeln(message.c_str());
                lcdConnector.lcdLoc(lcdConnector.line2);
                lcdConnector.typeln(numbers.substr(0, numbers.size() - 1).c_str());
            }
            if (numbers.back() == '#' && numbers.size() == 5) {
                std::cout << "entered code is : ";
                numbers.pop_back();

		        message = "Code: ";
		        message += numbers;

                lcdConnector.ClrLcd();
                lcdConnector.lcdLoc(lcdConnector.line1);
                lcdConnector.typeln(message.c_str());
                lcdConnector.lcdLoc(lcdConnector.line2);
                lcdConnector.typeln("Sending file");

                int result = handler(numbers);
                if (result == 0) {
                    std::cout << "Successful printing" << std::endl;
                    lcdConnector.ClrLcd();
                    lcdConnector.lcdLoc(lcdConnector.line1);
                    lcdConnector.typeln("Printing");
                    delay(5000);
                    lcdConnector.ClrLcd();
		        } else if (result == -1) {
                    std::cout << "Error. Something wrong." << std::endl;
                    lcdConnector.ClrLcd();

                    lcdConnector.lcdLoc(lcdConnector.line1);
                    lcdConnector.typeln("Incorrect code");
                    delay(2500);
                    lcdConnector.ClrLcd();
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

            lcdConnector.ClrLcd();
            message = "Nums is exceeded";
            lcdConnector.lcdLoc(lcdConnector.line1);
            lcdConnector.typeln(message.c_str());
            delay(2500);
            lcdConnector.ClrLcd();
            message = "Enter your code:";
            lcdConnector.lcdLoc(lcdConnector.line1);
            lcdConnector.typeln(message.c_str());

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
