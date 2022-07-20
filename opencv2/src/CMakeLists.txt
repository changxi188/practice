#add_library(my_lib SHARED 
#			lk.cpp)

#target_link_libraries(my_lib ${THIRD_PARTY})


#add_executable(main main.cpp)
#target_link_libraries(main ${THIRD_PARTY} my_lib)


add_executable(1 1.cpp)
target_link_libraries(1 ${THIRD_PARTY})

add_executable(111 111.cpp)
target_link_libraries(111 ${THIRD_PARTY})
