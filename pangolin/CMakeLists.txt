cmake_minimum_required(VERSION 2.8)

project(PANGOLIN)


find_package(Pangolin 0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


set(THIRD_PARTY_LIBS 
		${OpenCV_LIBS}
		${Pangolin_LIBRARIES}
)

add_executable(helloPangolin helloPangolin.cpp)
target_link_libraries(helloPangolin ${THIRD_PARTY_LIBS})

add_executable(pangolin_tutorial2 pangolin_tutorial2.cpp)
target_link_libraries(pangolin_tutorial2 ${THIRD_PARTY_LIBS})

add_executable(pangolin_tutorial3 pangolin_tutorial3.cpp)
target_link_libraries(pangolin_tutorial3 ${THIRD_PARTY_LIBS})

add_executable(pangolin_tutorial4 pangolin_tutorial4.cpp)
target_link_libraries(pangolin_tutorial4 ${THIRD_PARTY_LIBS})
