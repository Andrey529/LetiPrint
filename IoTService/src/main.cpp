#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <vector>
#include <wiringPi.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    static_cast<std::string *>(userdata)->append(static_cast<char *>(ptr), size * nmemb);
    return size * nmemb;
}

void printFile() {
    CURL *curl = curl_easy_init();

    if(curl) {
        std::string response;
        std::string url("httpbin.org/image/jpeg");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        /* ask libcurl to show us the verbose output */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

        /* Perform the request */
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        std::cout << res << std::endl;
        std::cout << response << std::endl;

        std::string fileName("test.jpeg");
        std::ofstream outfile ("/app/build/" + fileName);
        outfile << response;
        outfile.close();

        std::string printerName("HP_LaserJet_1018");
        std::string command = "lp -d " + printerName + " /app/build/" + fileName;
        std::system(command.c_str());
    }
}

#define ROWS 4
#define COLS 4

const int rowPins[ROWS] = { 2, 3, 11, 17 };
const int colPins[COLS] = { 27, 22, 10, 9 };

const char keys[ROWS][COLS] = {
        { '1', '2', '3', 'A' },
        { '4', '5', '6', 'B' },
        { '7', '8', '9', 'C' },
        { '*', '0', '#', 'D' }
};

void setup() {
    wiringPiSetupGpio();
    pinMode(26,OUTPUT);
    for (int i = 0; i < ROWS; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
    }
    for (int i = 0; i < COLS; i++) {
        pinMode(colPins[i], INPUT);
        pullUpDnControl(colPins[i], PUD_UP);
    }
}

char readKeypad() {
    for (int row = 0; row < ROWS; row++) {
        digitalWrite(rowPins[row], LOW);
        for (int col = 0; col < COLS; col++) {
            if (digitalRead(colPins[col]) == LOW) {
                digitalWrite(rowPins[row], HIGH);
                return keys[row][col];
            }
        }
        digitalWrite(rowPins[row], HIGH);
    }
    return '@';
}

int main(int argc, char **argv) {
    setup();
    std::vector<char> numbers;
    numbers.push_back('@');
    while (true) {
        char key = readKeypad();
        if (numbers.size() <= 5) {
            if (key == '*') {
                std::cout << "your code has been erased" << std::endl;
                numbers.clear();
            }
            if (key != '@') {
                if (numbers.back() == '@') {
                    numbers.pop_back();
                    numbers.push_back(key);
                }
            } else if (numbers.back() != '@') {
                numbers.push_back('@');
            }
            if (numbers.back() == '#') {
                std::cout << "entered code is : ";
                numbers.pop_back();
                if ((numbers[0] == '1') and (numbers[1] == '2') and (numbers[2] == '3') and (numbers[3] == '4'))
                {
                    digitalWrite(26,HIGH);
                    delay(500);
                    digitalWrite(26,LOW);
                    printFile();
                }
                for (char number: numbers)
                    std::cout << number;
                std::cout << std::endl;
                numbers.clear();
            }
        }
        else
        {
            std::cout << "count of number is exceeded";
            numbers.clear();
            numbers.push_back('@');
        }
        delay(50);

    }
}


