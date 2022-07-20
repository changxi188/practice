cmake_minimum_required(VERSION 2.8)
project(CMAKE_PRAC)

message(STATUS "this is binary dir" ${PROJECT_BINARY_DIR})
message(STATUS "this is source dir" ${CMAKE_PRAC_SOURCE_DIR})

add_subdirectory(src bin)

install(FILES COPYRIGHT README DESTINATION share/doc/)
install(PROGRAMS runhello.sh DESTINATION bin)
install(DIRECTORY doc/ DESTINATION share/doc/)
