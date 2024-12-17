cmake_minimum_required(VERSION 3.29)
project(lab_02)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(lab_02
    src/des.h
    src/main.cpp)
