#include "PrinterController.h"

void PrinterController::Print(const std::string &fileDirectory, const std::string &fileName) {
    fileName_ = fileName;
    fileDirectory_ = fileDirectory;

    if (fileName_.empty() && fileDirectory_.empty()) {
        std::cout << "file name and file directory for printing file is empty." << std::endl;
        return;
    }
    else if (fileName_.empty()) {
        std::cout << "file name for printing file is empty." << std::endl;
        return;
    } else if (fileDirectory_.empty()) {
        std::cout << "file directory for printing file is empty." << std::endl;
        return;
    }

    std::string command = "lp -d " + printerName_ + " " + fileDirectory_ + "/" + fileName_;
    std::system(command.c_str());
}
