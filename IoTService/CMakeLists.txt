cmake_minimum_required(VERSION 3.18)
project(IoTService)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

find_library(WIRINGPI_LIB wiringPi)
include_directories(/usr/include/wiringPi)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} ${CURL_LIBRARIES} ${WIRINGPI_LIB})