cmake_minimum_required(VERSION 3.10)

project(A1 LANGUAGES CXX)

set(A1 src/A11.cpp src/A12.cpp src/A13.cpp)
add_library(A1 SHARED ${A1})

target_include_directories(A1 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )



