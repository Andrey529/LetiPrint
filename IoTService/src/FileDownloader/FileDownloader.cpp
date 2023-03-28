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

    try {
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

                // parse json fields and remove quotation marks
                userId_ = json.at("userId").get<std::string>();
                userId_ = userId_.substr(1, userId_.size() - 2);
                linkToDownloadFile_ = json.at("fileLink").get<std::string>();
                linkToDownloadFile_ = linkToDownloadFile_.substr(1, linkToDownloadFile_.size() - 2);
                fileType_ = json.at("fileType").get<std::string>();
                fileType_ = fileType_.substr(1, fileType_.size() - 2);
                fileName_ = json.at("fileName").get<std::string>();
                fileName_ = fileName_.substr(1, fileName_.size() - 2);

                std::cout << "userId: " << userId_ << '\n'
                          << "linkToDownloadFile: " << linkToDownloadFile_ << '\n'
                          << "fileName: " << fileName_ << '\n'
                          << "fileType: " << fileType_ << std::endl;

                /* Perform the request to download file*/
                response.clear();

                curl_easy_setopt(curl, CURLOPT_URL, linkToDownloadFile_.c_str());
                result = curl_easy_perform(curl);
                curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
                if (http_code == 200 && result != CURLE_ABORTED_BY_CALLBACK) {
                    std::ofstream outFile(directoryToSaveTheFile_ + fileName_ + '.' + fileType_);
                    outFile << response;
                    outFile.close();
                    if (fileType_ == "docx" || fileType_ == "doc") {
                        std::string command;
                        command = "libreoffice --headless --convert-to pdf " + directoryToSaveTheFile_ +
                                fileName_ + '.' + fileType_ + " --outdir .";
                        std::cout << command << std::endl;
                        std::system(command.c_str());
                    }
                } else {
                    std::cout << "Bad request to download file with fileId = " << fileId_ << std::endl;
                    throw BadRequest("Bad request to download file.");
                }

            } else if (http_code == 204 && result != CURLE_ABORTED_BY_CALLBACK) {
                std::cout << "File with fileId = " + fileId_ + " does not exist" << std::endl;
                throw FileDoesNotExist();
            } else {
                std::cout << "Bad request to check fileId = " << fileId_ << std::endl;
                throw BadRequest("Bad request to check fileId.");
            }

        } else {
            throw std::runtime_error("Curl is invalid.");
        }
    }
    catch (const nlohmann::json::parse_error &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "parse error at byte " << e.byte << std::endl;
        throw JsonError();
    } catch (const nlohmann::json::type_error &e) {
        std::cerr << e.what() << std::endl;
        throw JsonError();
    } catch (const nlohmann::json::out_of_range &e) {
        std::cerr << e.what() << std::endl;
        throw JsonError();
    }

}

const std::string &FileDownloader::getFileName() const {
    return fileName_;
}

const std::string &FileDownloader::getFileType() const {
    return fileType_;
}

const std::string &FileDownloader::getLinkToDownloadFile() const {
    return linkToDownloadFile_;
}

const std::string &FileDownloader::getUserId() const {
    return userId_;
}

const std::string &FileDownloader::getDirectoryToSaveTheFile() const {
    return directoryToSaveTheFile_;
}

const std::string &FileDownloader::getLinkToCheckFileId() const {
    return linkToCheckFileId_;
}

const std::string &FileDownloader::getFileId() const {
    return fileId_;
}
