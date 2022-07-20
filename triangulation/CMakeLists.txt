cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -O2 ${SSE_FLAGS} -msse4")

find_package(OpenCV 3 REQUIRED)
find_package(Sophus REQUIRED)
find_package(Pangolin REQUIRED)


include_directories("/usr/include/eigen3"
                    ${OpenCV_INCLUDE_DIRS}
					${Sophus_INCLUDE_DIRS}
					${PROJECT_SOURCE_DIR}/include)

set(THIRD_PARTY_LIBS
	${OpenCV_LIBS}
	${Sophus_LIBS}
	${Pangolin_LIBRARIES})

add_subdirectory(src)
add_subdirectory(app)


