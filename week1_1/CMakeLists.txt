cmake_minimum_required(VERSION 3.5)
project(comp-prog-week1_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

set(SOURCE_FILES haplesshedonism.cpp)
add_executable(comp-prog-week1_1 ${SOURCE_FILES} haplesshedonism.cpp)