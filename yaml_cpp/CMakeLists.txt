cmake_minimum_required(VERSION 2.8)

project(YAML_TEST)

# Declaration of package required
# find_package(PkgConfig)
# pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

find_package(yaml-cpp REQUIRED)
include_directories(${YAML_INCLUDE_DIRS})
# target_link_libraries(${YAML_CPP_LIBRARIES})


# Define the executable and link the yaml libs
add_executable(read_yaml_file read_yaml_file.cpp)
target_link_libraries(read_yaml_file ${YAML_CPP_LIBRARIES})

# Define the executable and link the yaml libs
add_executable(test2 test2.cpp)
target_link_libraries(test2 ${YAMLCPP_LIBRARIES})
