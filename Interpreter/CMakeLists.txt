cmake_minimum_required(VERSION 3.8)
project(Interpreter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp parser.h)
add_executable(Binaryfuck ${SOURCE_FILES})