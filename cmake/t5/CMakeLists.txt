cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)

find_package(CURL)
if(CURL_FOUND)
	include_directories(${CURL_INCLUDE_DIR})
	set(THIRD_PARTY_LIBS 
			${CURL_LIBRARY}
			${OpenCV_LIBS})	
	message(STATUS "${CURL_LIBRARY}")
	message(STATUS "${OpenCV_LIBS}")
	message(STATUS "${THIRD_PARTY_LIBS}")
	message(STATUS curl)
else(CURL_FOUND)
	message(FATAL_ERROR "curl library not found")
endif(CURL_FOUND)

add_subdirectory(src)


