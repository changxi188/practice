cmake_minimum_required(VERSION 2.8)
project(GTSAM_VISUALIZE)

find_package(GTSAM REQUIRED)
find_package(Pangolin REQUIRED)

include_directories(${Panglin_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")


set(lib_sup 
    gtsam
    tbb
    ${Pangolin_LIBRARIES}
)


add_executable(1 1.cpp)
target_link_libraries(1 ${lib_sup})

add_executable(2 2.cpp)
target_link_libraries(2 ${lib_sup})
