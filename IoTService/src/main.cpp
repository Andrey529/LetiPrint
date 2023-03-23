#include "IoTService/IoTService.h"

int main(int argc, char **argv) {
//    IoTService::Run(argc, argv);

    FileDownloader fileDownloader;
    fileDownloader.downloadFile("/home/andrey/Projects/LetiPrint/IoTService/", "https://q2-u8ro.onrender.com/downloadFile", "4274");
}

