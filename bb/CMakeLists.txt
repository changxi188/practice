cmake_minimum_required(VERSION 2.8)

project(bb)

include_directories("/usr/include/eigen3")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(mm src/mm.cpp)
add_executable(TextQuery src/TextQuery.cpp)
add_executable(123123 src/123123.cpp)
add_executable(234 src/234.cpp)
add_executable(eigen src/eigen.cpp)
add_executable(random src/random.cpp)
