cmake_minimum_required(VERSION 3.18)
project(IoTService)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif ()

find_library(WIRINGPI_LIB wiringPi)
include_directories(/usr/include/wiringPi)

include_directories(${PROJECT_SOURCE_DIR}/include/json/include)
include_directories(${PROJECT_SOURCE_DIR}/include/lcdConnector)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp
        src/GPIOController/GPIOController.h src/GPIOController/GPIOController.cpp
        src/PrinterController/PrinterController.cpp src/PrinterController/PrinterController.h
        src/FileDownloader/FileDownloader.cpp src/FileDownloader/FileDownloader.h
        src/IoTService/IoTService.cpp src/IoTService/IoTService.h
        src/FileDownloader/FileDownloaderExceptions.h
        src/LcdConnector/LcdConnector.cpp src/LcdConnector/LcdConnector.h)


target_link_libraries(${CMAKE_PROJECT_NAME} ${CURL_LIBRARIES} ${WIRINGPI_LIB})