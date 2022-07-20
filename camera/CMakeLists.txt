cmake_minimum_required(VERSION 2.8)
project(camera)

find_package(OpenCV 3.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)


set(THIRED_PARTY_LIBS

	${OpenCV_LIBS}
	)
#add_executable(stereo_calib_and_rect src/stereo_calib_and_rect.cpp)
#target_link_libraries(stereo_calib_and_rect ${THIRED_PARTY_LIBS})

#add_subdirectory(src)
add_subdirectory(app)
