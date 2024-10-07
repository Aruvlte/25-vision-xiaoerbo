cmake_minimum_required(VERSION 3.10)

project(rmath)

add_library(rmath SHARED src/rmath.cpp)

target_include_directories(rmath PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include/opencv4
    
)


