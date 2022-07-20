cmake_minimum_required(VERSION 2.8)
project(google_log)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

add_executable(google_log google_log.cpp)
target_link_libraries(google_log ${GLOG_LIBRARIES} pthread)

add_executable(1 1.cpp)
target_link_libraries(1 ${GLOG_LIBRARIES})
