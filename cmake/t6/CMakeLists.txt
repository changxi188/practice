cmake_minimum_required(VERSION 2.8)

#set(CMAKE_MODULE_PATH dd)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(mylib REQUIRED QUIET)
if(mylib_FOUND)
	include_directories(${mylib_INCLUDE_DIR})
	set(THIRD_PARTY_LIBS ${mylib_LIB})
else(mylib_FOUND)
	MESSAGE(FATAL_ERROR "mylib not found")
endif(mylib_FOUND)

add_subdirectory(src)

