cmake_minimum_required(VERSION 2.8)
project(mutithread)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -pthread")
add_executable(2.1 2.1.cpp)
add_executable(2.2 2.2.cpp)
add_executable(2.3 2.3.cpp)
add_executable(2.4 2.4.cpp)
add_executable(6-2 6-2.cpp)
add_executable(6-4 6-4.cpp)
