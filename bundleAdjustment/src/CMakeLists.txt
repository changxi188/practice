add_library(my_lib SHARED
        curve_fitting_GN.cpp
        vertex.cpp
        edge.cpp
        problem.cpp
		curve_fitting_g2o.cpp
		pcl.cpp)
target_link_libraries(my_lib ${THRID_PARTY_LIBS})
