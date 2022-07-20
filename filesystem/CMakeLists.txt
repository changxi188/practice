cmake_minimum_required(VERSION 3.0)
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_executable(1 1.cpp)
target_link_libraries(1
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)


add_executable(2 2.cpp)

add_executable(3 3.cpp)

add_executable(4 4.cpp)
