#include <iostream>
#include <curl/curl.h>
#include <fstream>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    static_cast<std::string *>(userdata)->append(static_cast<char *>(ptr), size * nmemb);
    return size * nmemb;
}

int main(int argc, char **argv) {
    CURL *curl = curl_easy_init();

    if(curl) {
        std::string response;
        std::string url("https://example.com");
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

//        std::ofstream outfile ("/home/andrey/Projects/LetiPrint/IoTService/test.pdf");
//        outfile << response;
//        outfile.close();
    }
}


