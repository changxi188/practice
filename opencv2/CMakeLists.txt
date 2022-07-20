cmake_minimum_required(VERSION 2.8)
project(OPENCV2)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")


find_package(OpenCV 3.2 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)

set(THIRD_PARTY ${OpenCV_LIBS})

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

