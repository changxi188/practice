cmake_minimum_required(VERSION 3.4)
project(gtsam_demo)

find_package(GTSAM REQUIRED)
include_directories(${GTSAM_INCLUDE_DIR})

set(lib_sup 
	gtsam)

add_executable(simple_rotation simple_rotation.cpp)
target_link_libraries(simple_rotation ${lib_sup})

add_executable(self_calibration_example self_calibration_example.cpp)
target_link_libraries(self_calibration_example ${lib_sup})

# add_executable(math.pdf math.pdf.cpp)
# target_link_libraries(math.pdf ${lib_sup})


