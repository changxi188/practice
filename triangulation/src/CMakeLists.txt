add_library(my_lib SHARED
				orb.cpp
				pose_estimation_2d_2d.cpp
				triangulation.cpp)
target_link_libraries(my_lib ${THIRD_PARTY_LIBS})
