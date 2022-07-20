cmake_minimum_required(VERSION 2.8)
project(CN_BA_PNP)

set(CMAKE_CXX_FLAGS  "-std=c++11 -O3")

find_package(OpenCV 3 REQUIRED)
find_package(Sophus REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${Sophus_INCLUDE_DIRS} "/usr/include/eigen3")


add_executable(1 1.cpp)
target_link_libraries(1 ${OpenCV_LIBS})




