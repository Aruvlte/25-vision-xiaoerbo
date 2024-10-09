cmake_minimum_required(VERSION 3.10)


project(Zimiao)

find_package(OpenCV REQUIRED)

add_executable(zimiao zimiao1.cpp)


#target_include_directories(zimiao PUBLIC
 #   ${OpenCV_LIBS}
#)

target_link_libraries(
    zimiao PUBLIC
    ${OpenCV_LIBS}
)