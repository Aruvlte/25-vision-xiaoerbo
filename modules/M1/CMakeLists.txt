cmake_minimum_required(VERSION 3.10)

project(M1 LANGUAGES CXX)
add_library(M1 SHARED src/M1.cpp)
target_include_directories(M1 PUBLIC include)
target_link_libraries(M1 PUBLIC A1)
    
