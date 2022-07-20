cmake_minimum_required(VERSION 2.8)
project(bundleAdjustment)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(OpenCV 3 REQUIRED)
find_package(G2O REQUIRED)
find_package(Sophus REQUIRED)

find_package(PCL 1.2 REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(
        "/usr/include/eigen3"
        ${OpenCV_INCLUDE_DIRS}
        ${G2O_INCLUDE_DIRS}
        ${Sophus_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS})

set(THRID_PARTY_LIBS
        ${OpenCV_LIBS}
        g2o_core g2o_stuff
        ${PCL_LIBRARY_DIRS})


add_subdirectory(src)

add_executable(bundleAdjustment app/bundleAdjustment.cpp)
target_link_libraries(bundleAdjustment ${THRID_PARTY_LIBS} my_lib)
