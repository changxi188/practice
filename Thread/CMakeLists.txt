cmake_minimum_required(VERSION 3.10)

project(thread)


set(CMAKE_CXX_STANDARD 11)


set(THIRD_PARTY_LIBS

		pthread
)

add_executable(mutex mutex1.cpp)
#target_link_libraries(mutex pthread)
target_link_libraries(mutex ${THIRD_PARTY_LIBS})


add_executable(t_hello t_hello.cpp)
target_link_libraries(t_hello ${THIRD_PARTY_LIBS})


add_executable(t_contributer t_contributer.cpp)
target_link_libraries(t_contributer ${THIRD_PARTY_LIBS})

add_executable(t_111 t_111.cpp)
target_link_libraries(t_111 ${THIRD_PARTY_LIBS})

add_executable(mutex2 mutex2.cpp)
target_link_libraries(mutex2 ${THIRD_PARTY_LIBS})


add_executable(time_mutex time_mutex.cpp)
target_link_libraries(time_mutex ${THIRD_PARTY_LIBS})

add_executable(lock_guard_thread lock_guard_thread.cpp)
target_link_libraries(lock_guard_thread ${THIRD_PARTY_LIBS})


add_executable(unique_lock_thread unique_lock_thread.cpp)
target_link_libraries(unique_lock_thread ${THIRD_PARTY_LIBS})

add_executable(a a.cpp)
target_link_libraries(a ${THIRD_PARTY_LIBS})


add_executable(unique_lock_contri unique_lock_contri.cpp)
target_link_libraries(unique_lock_contri ${THIRD_PARTY_LIBS})

add_executable(unique_lock_move unique_lock_move.cpp)
target_link_libraries(unique_lock_move ${THIRD_PARTY_LIBS})

add_executable(unique_lock_owns_lock unique_lock_owns_lock.cpp)
target_link_libraries(unique_lock_owns_lock ${THIRD_PARTY_LIBS})


add_executable(CSAPP CSAPP.c)

add_executable(b 1.cpp)
