set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(libHello hello.cpp)
add_library(mylib SHARED ${libHello})
set_target_properties(mylib PROPERTIES VERSION 1.2 SOVERSION 3)

add_library(mylib_static STATIC ${libHello})
set_target_properties(mylib_static PROPERTIES OUTPUT_NAME "mylib")

install(TARGETS mylib mylib_static
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/hello.h 
		DESTINATION include/hello)
