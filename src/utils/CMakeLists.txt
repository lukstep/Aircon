project(utils)

message(STATUS "${PROJECT_NAME} setup")

add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} pico_stdlib
                                      pico_util
                                      platform)