#include "FileDownloader.h"

FileDownloader::FileDownloader() {
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    /* ask libcurl to show us the verbose output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
}

FileDownloader::~FileDownloader() {
    curl_easy_cleanup(curl);
}

size_t FileDownloader::write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    static_cast<std::string *>(userdata)->append(static_cast<char *>(ptr), size * nmemb);
    return size * nmemb;
}

void FileDownloader::downloadFile(const std::string &directoryToSaveTheFile, const std::string &linkToCheckFileId,
                                  const std::string &fileId) {
    directoryToSaveTheFile_ = directoryToSaveTheFile;
    linkToCheckFileId_ = linkToCheckFileId;
    fileId_ = fileId;

    if (directoryToSaveTheFile_.empty() || linkToCheckFileId_.empty() || fileId_.empty()) {
        throw std::invalid_argument("Invalid arguments. Both function parameters should not be empty.");
    }

    if (curl) {
        linkToCheckFileId_ += "?fileId=" + fileId_;

        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, linkToCheckFileId_.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        /* Perform the request to check file with file id is exist*/
        CURLcode result = curl_easy_perform(curl);
        long http_code = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

        if (http_code == 200 && result != CURLE_ABORTED_BY_CALLBACK) {
            std::cout << response << std::endl;
            nlohmann::json json = nlohmann::json::parse(response);

            std::string userId = json.at("userId").get<std::string>();
            std::string linkToDownloadFile = json.at("fileLink").get<std::string>();
            std::string fileType = json.at("fileType").get<std::string>();
            std::string fileName = json.at("fileName").get<std::string>();

            std::cout << userId << '\n' << linkToDownloadFile << '\n' << fileType << '\n' << fileName << std::endl;

            /* Perform the request to download file*/
            response.clear();
            curl_easy_setopt(curl, CURLOPT_URL, linkToDownloadFile.c_str());
            result = curl_easy_perform(curl);
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
            if (http_code == 200 && result != CURLE_ABORTED_BY_CALLBACK) {
                std::ofstream outFile(directoryToSaveTheFile_ + fileName + "." + fileType);
                outFile << response;
                outFile.close();
            } else {
                std::cout << "Something wrong" << std::endl;
            }

        } else if (http_code == 204 && result != CURLE_ABORTED_BY_CALLBACK) {
            std::cout << "File with fileId = " + fileId_ + " does not exist" << std::endl;
        } else {
            std::cout << "Something wrong" << std::endl;
        }

    } else {
        throw std::runtime_error("Curl is invalid.");
    }

}
