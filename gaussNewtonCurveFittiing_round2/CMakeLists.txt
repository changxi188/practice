cmake_minimum_required(VERSION 2.8)
project(GN_Round2)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(OpenCV REQUIRED)
find_package(G2O REQUIRED)



include_directories("/usr/include")
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${G2O_INCLUDE_DIRS})

set(THIRD_PARTY_LIBS
		${G2O_CORE_LIBRARY}
		${G2O_STUFF_LIBRARY}
		${OpenCV_LIBS}
		)


add_executable(curvefitting_GN_self curvefitting_GN_self.cpp)
target_link_libraries(curvefitting_GN_self ${THIRD_PARTY_LIBS})

add_executable(curvefitting_G2O curvefitting_G2O.cpp)
target_link_libraries(curvefitting_G2O ${THIRD_PARTY_LIBS})
