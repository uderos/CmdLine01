cmake_minimum_required (VERSION 2.8.11)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror ")
if (LINUX)
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lpthread")
endif (LINUX)

SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_SOURCE_DIR})
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/cmdline_lib)

project (cmdline01)

add_subdirectory (cmdline_lib)
add_subdirectory (unit_test)

