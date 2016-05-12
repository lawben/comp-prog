cmake_minimum_required(VERSION 3.5)
project(comp-prog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES week4)
add_executable(comp-prog ${SOURCE_FILES} week4/tightwords.cpp)