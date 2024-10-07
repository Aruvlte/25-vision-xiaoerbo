cmake_minimum_required(VERSION 3.10)

project(math)
add_library(math SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/Math.cpp)

target_include_directories(math PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include/opencv4
)
