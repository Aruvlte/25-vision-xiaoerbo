cmake_minimum_required(VERSION 3.10)

project(assembly2)

add_library(assembly2 SHARED src/assembly2.cpp)

target_include_directories(assembly2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include/opencv4
    
)