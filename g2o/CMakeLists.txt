cmake_minimum_required(VERSION 2.8)
project(gaussNewton)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories("/usr/include/eigen3/")

find_package(OpenCV 3.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)



set(THIRED_PARTY_LIBS
        ${OpenCV_LIBS}
        g2o_core g2o_stuff)


add_executable(gaussNewton src/gaussNewton.cpp)
target_link_libraries(gaussNewton ${THIRED_PARTY_LIBS})

add_executable(g2oCurveFitting src/g2oCurveFitting.cpp)
target_link_libraries(g2oCurveFitting ${THIRED_PARTY_LIBS})
