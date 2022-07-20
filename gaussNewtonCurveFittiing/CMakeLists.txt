cmake_minimum_required(VERSION 2.8)
project(GNCurveFitring)

# set cmake flags
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++14 -O3")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# find packages
find_package(G2O REQUIRED)
find_package(OpenCV REQUIRED)

# include directories
include_directories("/usr/include/eigen3"
					${PROJECT_SOURCE_DIR}/include
					${G2O_INCLUDE_DIRS}
					${OpenCV_INCLUDE_DIRS}
					)
					
# set third party libs
set(THIRD_PARTY_LIBS
		${G2O_CORE_LIBRARY}
		${G2O_STUFF_LIBRARY}
		${OpenCV_LIBS}
		)


# add subdirectries
add_subdirectory(src)
add_subdirectory(app)
