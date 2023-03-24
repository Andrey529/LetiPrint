#ifndef IOTSERVICE_FILEDOWNLOADEREXCEPTIONS_H
#define IOTSERVICE_FILEDOWNLOADEREXCEPTIONS_H

#include <stdexcept>
#include <string>

class FileDoesNotExist : public std::exception {
private:
    const char *message_;
public:
    FileDoesNotExist() : message_("File does not exist.") { }
    FileDoesNotExist(const char *message) : message_(message) {}

    const char *what() const throw() override {
        return message_;
    }
};


class BadRequest : public std::exception {
private:
    const char *message_;
public:
    BadRequest() : message_("Bad request.") { }
    BadRequest(const char *message) : message_(message) {}

    const char *what() const throw() override {
        return message_;
    }
};

class JsonError : public std::exception {
private:
    const char *message_;
public:
    JsonError() : message_("Json error.") { }
    JsonError(const char *message) : message_(message) {}

    const char *what() const throw() override {
        return message_;
    }
};


#endif //IOTSERVICE_FILEDOWNLOADEREXCEPTIONS_H
