cmake_minimum_required(VERSION 2.8)
project(ORB)

find_package(OpenCV 3.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")

include_directories(${PROJECT_SOURCE_DIR}/include)


set(THIRED_PARTY
        ${OpenCV_LIBS})

add_executable(orb_cv src/orb_cv.cpp)
target_link_libraries(orb_cv ${THIRED_PARTY})

add_executable(orb_self src/orb_self.cpp)
target_link_libraries(orb_self ${THIRED_PATRY})
