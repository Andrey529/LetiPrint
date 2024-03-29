#ifndef IOTSERVICE_PRINTERCONTROLLER_H
#define IOTSERVICE_PRINTERCONTROLLER_H

#include <string>
#include <iostream>

class PrinterController {
private:
    const std::string printerName_;
    std::string fileName_;
    std::string fileDirectory_;
    std::string fileType_;
public:
    explicit PrinterController(const std::string &printerName) : printerName_(printerName) {}

    void Print(const std::string &fileDirectory, const std::string &fileName, const std::string &fileType);
};

#endif //IOTSERVICE_PRINTERCONTROLLER_H
