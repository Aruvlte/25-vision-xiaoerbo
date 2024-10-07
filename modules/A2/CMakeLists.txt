cmake_minimum_required(VERSION 3.10)

project(A2)
add_library(A2 SHARED src/A2.cpp)
target_include_directories(A2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
