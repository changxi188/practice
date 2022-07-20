cmake_minimum_required(VERSION 2.8)
project(ch12)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)


add_subdirectory(src)


add_executable(set_and_map set_and_map.cpp)
add_executable(ch12.3 ch12.3.cpp)
target_link_libraries(ch12.3 query)
