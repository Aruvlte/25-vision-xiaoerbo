cmake_minimum_required(VERSION 3.10)

project(m2 LANGUAGES CXX)
add_library(M2 SHARED src/M2.cpp)

target_include_directories(M2 PUBLIC
    ${kalman_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include/opencv4
)
target_link_libraries(M2 PUBLIC A1)
target_link_libraries(M2 PUBLIC A2)