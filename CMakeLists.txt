cmake_minimum_required(VERSION 2.4)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -O3 -pthread -Wfatal-errors")

include_directories(
	generated/include/
	lib/virtual-network-layers-cpp/include/
)

add_subdirectory(generated)
add_subdirectory(lib)
add_subdirectory(src)


