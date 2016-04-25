cmake_minimum_required(VERSION 3.5)
project(comp-prog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

set(SOURCE_FILES week1_2/mirroredpalindrome.cpp)
add_executable(comp-prog ${SOURCE_FILES} week1_2/mirroredpalindrome.cpp)