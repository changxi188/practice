cmake_minimum_required(VERSION 2.8)
project(CMAKE_PRAC)

message(STATUS "this is binary dir" ${PROJECT_BINARY_DIR})
message(STATUS "this is source dir" ${CMAKE_PRAC_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(app)

install(FILES COPYRIGHT README DESTINATION share/doc/)
install(PROGRAMS runhello.sh DESTINATION bin)
install(DIRECTORY doc/ DESTINATION share/doc/)
