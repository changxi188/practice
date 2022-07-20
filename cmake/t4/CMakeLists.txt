cmake_minimum_required(VERSION 2.8)

include_directories("/home/mr/Downloads/practice/cmake/t3_install/include")

FIND_LIBRARY(myLib mylib)
IF(myLib)
message(STATUS "find mylib111111111111")
set(THIRD_PARTY ${myLib})
ENDIF(myLib)

add_subdirectory(src)
