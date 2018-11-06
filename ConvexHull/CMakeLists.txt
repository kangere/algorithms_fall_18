project(hull CXX)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "-std=c++1z")

add_executable( hull
		main.cpp
		point.cpp
		utils.cpp)