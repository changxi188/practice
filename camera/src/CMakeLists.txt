add_library(sm_lib SHARED
				chessboard_images.cpp
				stereo_calib_and_rect.cpp
			)

target_link_libraries(sm_lib ${THIRD_PATRY_LIBS})
