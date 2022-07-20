cmake_minimum_required(VERSION 2.8)
project(GCC)

set(CMAKE_BUILD_TYPE "Debug")

# -std=c++11 : c++11; -g : 调试信息; -Wall : 开启所有警告;
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")


# -O0 : 调试包不优化
set(CMAKE_CXX_FLAGS_DEBUG "-O0")

add_executable(hello hello.cpp)
