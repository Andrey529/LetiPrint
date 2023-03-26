#ifndef IOTSERVICE_FILEDOWNLOADER_H
#define IOTSERVICE_FILEDOWNLOADER_H

#include <string>
#include <iostream>
#include <fstream>

#include <curl/curl.h>
#include "nlohmann/json.hpp"

#include "FileDownloaderExceptions.h"

class FileDownloader {
private:
    CURL *curl;
    std::string directoryToSaveTheFile_;
    std::string linkToCheckFileId_;
    std::string fileId_;
    std::string userId_;
    std::string linkToDownloadFile_;
    std::string fileName_;
    std::string fileType_;
public:
    FileDownloader();

    ~FileDownloader();

    static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

    void downloadFile(const std::string &directoryToSaveTheFile, const std::string &linkToCheckFileId,
                      const std::string &fileId);

    [[nodiscard]] const std::string& getDirectoryToSaveTheFile() const;
    [[nodiscard]] const std::string& getLinkToCheckFileId() const;
    [[nodiscard]] const std::string& getFileId() const;
    [[nodiscard]] const std::string& getUserId() const;
    [[nodiscard]] const std::string& getLinkToDownloadFile() const;
    [[nodiscard]] const std::string& getFileName() const;
    [[nodiscard]] const std::string& getFileType() const;
};

#endif //IOTSERVICE_FILEDOWNLOADER_H
