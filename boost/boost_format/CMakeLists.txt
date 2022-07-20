find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(boost_format boost_format.cpp)
target_link_libraries(boost_format ${Boost_LIBRARIES})

