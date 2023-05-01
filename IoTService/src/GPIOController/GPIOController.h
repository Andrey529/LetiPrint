#ifndef IOTSERVICE_GPIOCONTROLLER_H
#define IOTSERVICE_GPIOCONTROLLER_H

#include <iostream>
#include <vector>
#include <wiringPi.h>
#include <functional>
#include "../LcdConnector/LcdConnector.h"

class GPIOController {
public:
    const int rows_ = 4;
    const int columns_ = 4;
    const std::vector<int> rowPins_ = {13, 19, 11, 17}; // {2, 3, 11, 17}
    const std::vector<int> columnPins_ = {27, 22, 10, 9};
    const std::vector<std::vector<char>> keys_ = {{'1', '2', '3', 'A'},
                                                  {'4', '5', '6', 'B'},
                                                  {'7', '8', '9', 'C'},
                                                  {'*', '0', '#', 'D'}};
    LcdConnector lcdConnector;
    int I2CAddress = 0x27;
public:
    GPIOController() = default;

    GPIOController(const int &rows, const int &columns, const std::vector<int> &rowPins,
                   const std::vector<int> &columnPins, const std::vector<std::vector<char>> &keys)
            : rows_(rows), columns_(columns), rowPins_(rowPins), columnPins_(columnPins), keys_(keys) {}

    GPIOController(const int &rows, const int &columns, std::vector<int> &&rowPins,
                   std::vector<int> &&columnPins, std::vector<std::vector<char>> &&keys)
            : rows_(rows), columns_(columns), rowPins_(std::move(rowPins)), columnPins_(std::move(columnPins)),
              keys_(std::move(keys)) {}

    void Run(std::function<int (std::string)> handler);

    void setup();

    char readKeypad();

};

#endif //IOTSERVICE_GPIOCONTROLLER_H
