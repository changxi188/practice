cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -pthread")


include_directories(${PROJECT_SOURCE_DIR}/include)
# add_executable(clause7 clause7.cpp)
add_subdirectory(src)
