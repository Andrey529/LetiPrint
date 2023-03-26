#include "IoTService.h"

void IoTService::Run(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Wrong number of arguments. Should be 4 arguments:\n" <<
                  "./IoTService <printer name> <directory to save downloaded files>" <<
                  "<link to check fileId on BackendService>" << std::endl;
    }

    const std::string printerName = argv[1];
    const std::string directoryToSaveTheFile = argv[2];
    const std::string linkToCheckFileId = argv[3];

    FileDownloader fileDownloader_;
    PrinterController printerController_(printerName);

    auto handler = [&fileDownloader_, &printerController_, &directoryToSaveTheFile, &linkToCheckFileId](
            const std::string &fileId) -> int {
        try {
            fileDownloader_.downloadFile(directoryToSaveTheFile, linkToCheckFileId, fileId);
            printerController_.Print(directoryToSaveTheFile, fileDownloader_.getFileName(),
                                     fileDownloader_.getFileType());
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
        return 0;
    };

    GPIOController gpioController_;
    gpioController_.Run(handler);

}
