cmake_minimum_required(VERSION 3.0)

project(app)

add_definitions("-std=c++11")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(include)

add_executable(${PROJECT_NAME}
	srcs/main.cpp
	srcs/Application.cpp
	include/Application.hpp
)

target_link_libraries(${PROJECT_NAME} stdc++fs)