#ifndef IOTSERVICE_FILEDOWNLOADER_H
#define IOTSERVICE_FILEDOWNLOADER_H

#include <string>
#include <iostream>
#include <curl/curl.h>
#include <fstream>

#include "nlohmann/json.hpp"

class FileDownloader {
private:
    CURL *curl;
    std::string directoryToSaveTheFile_;
    std::string linkToCheckFileId_;
    std::string fileId_;
public:
    FileDownloader();

    ~FileDownloader();

    static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

    void downloadFile(const std::string &directoryToSaveTheFile, const std::string &linkToCheckFileId,
                      const std::string &fileId);

};

#endif //IOTSERVICE_FILEDOWNLOADER_H
