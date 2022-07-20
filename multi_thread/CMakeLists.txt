cmake_minimum_required(VERSION 2.8)
project(multi_thread)

set(CMAKE_CXX_FLAG "-std=c++11 -Wall -O3 -pthread")

include_directories(${PROJECT_SOURCE_DIR}/include)


add_subdirectory(src)

add_executable(run_vo app/run_vo.cpp)
target_link_libraries(run_vo pthread my_lib)

