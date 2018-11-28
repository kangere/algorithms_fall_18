project(seam CXX)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "-std=c++1z")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_executable(seam 
	main.cpp
	matrix.cpp)

add_custom_command(TARGET seam POST_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test.pgm $<TARGET_FILE_DIR:seam>)