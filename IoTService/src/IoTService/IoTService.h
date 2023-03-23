#ifndef IOTSERVICE_IOTSERVICE_H
#define IOTSERVICE_IOTSERVICE_H

#include <string>

#include "../GPIOController/GPIOController.h"
#include "../FileDownloader/FileDownloader.h"
#include "../PrinterController/PrinterController.h"

class IoTService {
public:
    IoTService() = delete;
    static void Run(int argc, char **argv);
};

#endif //IOTSERVICE_IOTSERVICE_H
