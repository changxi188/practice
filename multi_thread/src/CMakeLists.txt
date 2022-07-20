add_library(my_lib SHARED
	frontend.cpp
	map.cpp
	viewer.cpp
	)
target_link_libraries(my_lib pthread)
