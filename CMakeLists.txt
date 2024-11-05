cmake_minimum_required(VERSION 3.30)

# set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc CACHE PATH "" FORCE)
# set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++ CACHE PATH "" FORCE)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(PICO_BOARD pico_w)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(aircon LANGUAGES C CXX ASM VERSION 0.0.1)

add_compile_options(-Wall -Wextra -Wno-psabi -fno-exceptions -g -Os)

pico_sdk_init()


if ("$ENV{WIFI_SSID}" STREQUAL "")
    message(FATAL_ERROR "WIFI_SSID enviroment variable is not defined")
elseif ("$ENV{WIFI_PASSWORD}" STREQUAL "")
    message(FATAL_ERROR "WIFI_PASSWORD enviroment variable is not defined")
else()
    add_subdirectory(src)
endif()
