cmake_minimum_required(VERSION 2.9)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

message("SS : ${CMAKE_MODULE_PATH}")

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

function(MY_PARSE target)
    cmake_parse_arguments(STUDENT "ADULT" "NAME;AGE" "SCORE" ${ARGN})
    # 通过 prefix_参数名: 例如 STUDENT_ADULT
    message("target name ${target}")
    message("isadult  = ${STUDENT_ADULT}")
    message("name  = ${STUDENT_NAME}")
    message("age  = ${STUDENT_AGE}")
    message("score  = ${STUDENT_SCORE}")

    message("ARGN = ${ARGN}")
    message("ARGV = ${ARGV}")
    message("ARGC = ${ARGC}")
endfunction()
MY_PARSE(aa NAME zhangsan AGE 20 SCORE 100 200 300 ADULT 400 500 )


set(third_sup
    ${GLOG_LIBRARIES}
    ${CERES_LIBRARIES}
)


add_executable(1 1.cpp)
target_link_libraries(1 ${third_sup})
