cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS system program_options REQUIRED)

# find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(1 1.cpp)
target_link_libraries(1 ${Boost_LIBRARIES})

