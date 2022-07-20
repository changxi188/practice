cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -O3 -Wall")

add_executable(2.1.1 2.1.1.cpp)

add_executable(test_ref test.cpp)
