add_executable(test test.cpp)

add_executable(1 1.cpp)
target_link_libraries(1 pthread)

add_executable(lock_free_stack lock_free_stack.cpp)
target_link_libraries(lock_free_stack pthread)

add_executable(lock_free_queue lock_free_queue.cpp)
target_link_libraries(lock_free_queue pthread)
