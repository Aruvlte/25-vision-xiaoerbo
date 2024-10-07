cmake_minimum_required(VERSION 3.10)

project(module2)




set(SOURCES_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include/robotlab/opcua_cs)

set(SOURCES src/argument.cpp src/client.cpp src/open62541.c src/object.cpp src/server.cpp src/variable.cpp)

add_library(module2 SHARED ${SOURCES})

target_include_directories(module2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SOURCES_INCLUDE}

)
target_link_libraries(module2 PUBLIC pthread)