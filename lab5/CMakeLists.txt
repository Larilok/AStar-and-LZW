cmake_minimum_required(VERSION 3.10)
project(lab5)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp dictionary.h operations.h map.h)

add_executable(lab5 ${SOURCE_FILES})