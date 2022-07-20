cmake_minimum_required(VERSION 2.8)


project(CurveFitting)

list(APPEND CMAKE_MODULE_PATH /home/holo/practice/g2o/cmake)


include_directories("/usr/include/eigen3")


find_package(OpenCV 3.2 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


find_package(GTSAM REQUIRED)


find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})


find_package(PCL 1.3 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


set(THIRD_PARTY ${OpenCV_LIBS} ${PCL_LIBRARIES} gtsam tbb ${G2O_CORE_LIBRARY} ${G2O_STUFF_LIBRARY})

add_executable(1 1.cpp)
target_link_libraries(1 ${THIRD_PARTY})


