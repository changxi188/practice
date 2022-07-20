cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -pthread")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main src/main.cpp src/Time.cpp)
add_executable(3-7 src/3-7.cpp src/Human.cpp src/Men.cpp src/Women.cpp)
add_executable(3-9 src/3-9.cpp src/B.cpp)
add_executable(3-11 src/3-11.cpp src/Human.cpp src/Men.cpp src/Women.cpp)
add_executable(3-12 src/3-12.cpp)
add_executable(3-13 src/3-13.cpp)
add_executable(3-14 src/3-14.cpp)
add_executable(3-15 src/3-15.cpp)
add_executable(3-16 src/3-16.cpp)

add_executable(1 1.cpp)
