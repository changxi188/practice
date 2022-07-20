add_library(my_lib SHARED 
	#g2o_GN_curve_fitting.cpp
					self_GN_curve_fitting.cpp)
target_link_libraries(my_lib ${THIRD_PARTY_LIBS})
