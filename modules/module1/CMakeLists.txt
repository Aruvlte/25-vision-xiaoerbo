cmake_minimum_required(VERSION 3.10)

project(module1)


add_library(module1 SHARED src/module1a/m1.cpp src/module1a/m2.cpp src/module1a/m3.cpp src/module1a/m4.cpp src/module1b/module1b.cpp)

target_include_directories(module1 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include/opencv4
    
)

target_link_libraries(module1 PUBLIC assembly2)