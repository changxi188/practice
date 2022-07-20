cmake_minimum_required(VERSION 3.16)
project(vo_by_self)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(OpenCV 3.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")
include_directories(${PROJECT_SOURCE_DIR}/include)

set(THIRED_PARTY_LIBS
        ${OpenCV_LIBS}
        g2o_core g2o_stuff)

add_executable(pose_estimation_2d2d src/pose_estimation_2d2d.cpp)
target_link_libraries(pose_estimation_2d2d ${THIRED_PARTY_LIBS})

add_executable(triangulation src/triangulation.cpp)
target_link_libraries(triangulation ${THIRED_PARTY_LIBS})

add_executable(pose_estimation_3d2d src/pose_estimation_3d2d.cpp)
target_link_libraries(pose_estimation_3d2d ${THIRED_PARTY_LIBS})