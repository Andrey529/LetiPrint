#include "PrinterController.h"

void PrinterController::Print(const std::string &fileDirectory, const std::string &fileName, const std::string &fileType) {
    fileName_ = fileName;
    fileDirectory_ = fileDirectory;
    fileType_ = fileType;

    if (fileName_.empty() || fileDirectory_.empty() || fileType_.empty()) {
        throw std::invalid_argument("file name, file directory and file type for printing file should not be empty.");
    }

    std::cout << "Печатается файл\n"
                 "В дериктории: " << fileDirectory_ << '\n' <<
                 "C названием: " << fileName_ << '\n' <<
                 "C типом файла: " << fileType_ << std::endl;

    std::string command = "lp -d " + printerName_ + " " + fileDirectory_ + fileName_ + '.' + fileType_;
    std::system(command.c_str());
}
