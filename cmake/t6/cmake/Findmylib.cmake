FIND_PATH(mylib_INCLUDE_DIR hello.h /home/mr/Downloads/practice/cmake/t3_install/include/hello)
FIND_LIBRARY(mylib_LIB mylib  /home/mr/Downloads/practice/cmake/t3_install/lib)

message(STATUS ${mylib_INCLUDE_DIR})
message(STATUS ${mylib_LIB})
if(mylib_INCLUDE_DIR AND mylib_LIB)
	set(mylib_FOUND TRUE)
endif(mylib_INCLUDE_DIR AND mylib_LIB)

if (mylib_FOUND)
	if (NOT HELLO_FIND_QUIETLY)
		message(STATUS "found mylib : ${mylib_LIB}")
	endif (NOT HELLO_FIND_QUIETLY)
else (mylib_FOUND)
	if (mylib_FIND_REQUIRED)
		message(FATAL_ERROR "could not find hello library")
	endif (mylib_FIND_REQUIRED)
endif(mylib_FOUND)
