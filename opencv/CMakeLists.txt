cmake_minimum_required(VERSION 2.8)
project(DisplayImage)

find_package(OpenCV 3.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


set(third_libs ${OpenCV_LIBS})

add_executable(DisplayImage src/DisplayImage.cpp)
target_link_libraries(DisplayImage ${third_libs})

add_executable(GFTTDetector src/GFTTDetector.cpp)
target_link_libraries(GFTTDetector ${third_libs})


add_executable(LK src/LK.cpp)
target_link_libraries(LK ${third_libs})

add_executable(test_vcon src/test_vcon.cpp)
target_link_libraries(test_vcon ${third_libs})
