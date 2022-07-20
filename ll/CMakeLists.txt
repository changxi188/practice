cmake_minimum_required(VERSION 3.16)
project(ll)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(libs src/QueryResult.cpp src/TextQuery.cpp)

add_executable(ll main.cpp)
target_link_libraries(ll libs)
