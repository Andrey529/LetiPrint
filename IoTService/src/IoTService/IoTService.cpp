#include "IoTService.h"

void IoTService::Run(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Wrong number of arguments. Should be 4 arguments:\n" <<
            "./IoTService <printer name> <directory to save downloaded files>" <<
            "<link to check fileId on BackendService>" << std::endl;
    }

    std::string printerName = argv[1];
    std::string directoryToSaveTheFile = argv[2];
    std::string linkToCheckFileId = argv[3];

    FileDownloader fileDownloader_;
    PrinterController printerController_(printerName);

    auto handler = [&fileDownloader_, &printerController_]() -> void {

    };

    int rows;
    int columns;
    std::vector<int> rowPins;
    std::vector<int> columnPins;

    GPIOController gpioController_;
    gpioController_.Run();

}
