add_executable(start_g2o_GN ../src/g2o_GN_curve_fitting.cpp)
target_link_libraries(start_g2o_GN my_lib ${THIRD_PARTH_LIBS})

add_executable(start_self_GN start_self_GN.cpp)
target_link_libraries(start_self_GN my_lib ${THIRD_PARTH_LIBS})
