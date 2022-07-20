cmake_minimum_required(VERSION 2.8)
project(Class)

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories("/usr/include/eigen3")


add_executable(main src/main.cpp src/Human.cpp src/Men.cpp)

add_executable(5-1 src/5-1.cpp)
add_executable(5-2 src/5-2.cpp)
add_executable(5-3 src/5-3.cpp)
add_executable(file src/file.cpp)
add_executable(singleTon src/singleton.cpp)
add_executable(tempVariable src/tempVariable.cpp)
add_executable(map src/map.cpp)
