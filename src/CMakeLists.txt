message(STATUS "Setup ${CMAKE_PROJECT_NAME} build")

add_subdirectory(utils)
add_subdirectory(platform)
add_subdirectory(network)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 1)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE   
    WIFI_SSID=\"$ENV{WIFI_SSID}\"
    WIFI_PASSWORD=\"$ENV{WIFI_PASSWORD}\"
    MQTT_USER=\"$ENV{MQTT_USER}\"
    MQTT_PASSWORD=\"$ENV{MQTT_PASSWORD}\"
    SW_VERSION=\"${CMAKE_PROJECT_VERSION}\")

target_link_libraries(${CMAKE_PROJECT_NAME} utils network pico_stdlib)

set(EXECUTABLE_PATH "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_FILE}${CMAKE_PROJECT_NAME}.elf")
file(WRITE "${CMAKE_BINARY_DIR}/executable_path.txt" "${EXECUTABLE_PATH}\n")