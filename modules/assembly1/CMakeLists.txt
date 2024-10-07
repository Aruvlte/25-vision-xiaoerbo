cmake_minimum_required(VERSION 3.10)

project(assembly1)

add_library(assembly1 SHARED src/assembly1.cpp test/assembly1_test.cpp)

target_include_directories(assembly1 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    
)
