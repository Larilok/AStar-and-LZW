cmake_minimum_required(VERSION 3.10)
project(lab4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



include_directories(src)

add_library(a-star src/Astar.cpp)



add_executable(main main2.cpp)

target_link_libraries(main a-star)