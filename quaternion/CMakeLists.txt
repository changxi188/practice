include_directories("/usr/include/eigen3")

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS  "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

add_executable(1 1.cpp)
add_executable(2 2.cpp)
