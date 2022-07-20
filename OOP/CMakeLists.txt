cmake_minimum_required(VERSION 3.16)
project(OOP)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(abc SHARED
        src/Bulk_quote.cpp
        src/Quote.cpp
        src/Disc_quote.cpp)


add_executable(main main.cpp)
target_link_libraries(main abc)
