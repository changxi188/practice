cmake_minimum_required(VERSION 2.8)
project(gtest_demo)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pthread")

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(THIRD_PARTY_LIBS ${GTEST_BOTH_LIBRARIES})

enable_testing()

add_executable(main src/main.cpp src/add1.cpp)
target_link_libraries(main ${THIRD_PARTY_LIBS})
add_executable(test_add test/test_add.cpp src/add1.cpp)
target_link_libraries(test_add ${THIRD_PARTY_LIBS})

# add_subdirectory(src)
# add_subdirectory(test)
