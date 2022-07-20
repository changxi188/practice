cmake_minimum_required(VERSION 2.8)
project(PCL_PROJECT)
set(CMAKE_CXX_STANDARD 14)
find_package(PCL 1.3 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})

add_definitions(${PCL_DEFINITIONS})
add_executable(1 1.cpp)
target_link_libraries(1 ${PCL_LIBRARIES})


add_definitions(${PCL_DEFINITIONS})
add_executable(2 2.cpp)
target_link_libraries(2 ${PCL_LIBRARIES} pthread)

