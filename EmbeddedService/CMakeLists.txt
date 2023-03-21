cmake_minimum_required(VERSION 3.16)
project(EmbeddedService)

set(CMAKE_CXX_STANDARD 20)

find_library(WIRINGPI_LIB wiringPi)

include_directories(/usr/include/wiringPi)

add_executable(EmbeddedService src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} ${WIRINGPI_LIB})