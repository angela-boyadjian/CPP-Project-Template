cmake_minimum_required(VERSION 3.0)

project(cmake_test)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test executable
include_directories(../include)

add_library(func
	../srcs/Skat.cpp
	../include/Skat.hpp
)

set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch)
