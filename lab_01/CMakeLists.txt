cmake_minimum_required(VERSION 3.16)

project(da_lab_01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(da_lab_01_app main.cpp)

configure_file(input.txt input.txt COPYONLY)