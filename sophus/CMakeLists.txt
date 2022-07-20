cmake_minimum_required(VERSION 2.8)

project(SOPHUS_USE)

include_directories("/usr/include/eigen3")

find_package(Sophus REQUIRED)

include_directories(${Sophus_INCLUDE_DIRS})

add_executable(1 1.cpp)
# target_link_libraries(1  fmt::fmt)

install(FILES 1.cpp DESTINATION ${PROJECT_SOURCE_DIR}/include)
