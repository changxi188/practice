cmake_minimum_required(VERSION 2.8)
project(IOstream)

set(CMAKE_BUILD_TYPE Debug)

include_directories("/usr/include/eigen3")
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(iostream src/iostream.cpp)


