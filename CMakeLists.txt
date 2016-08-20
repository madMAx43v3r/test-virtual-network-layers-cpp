cmake_minimum_required(VERSION 2.4)
cmake_policy(SET CMP0015 NEW)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -O3 -pthread -Wfatal-errors")

include_directories(
	generated/include/
	lib/virtual-network-layers-cpp/include/
)

link_directories(generated/)

add_subdirectory(generated)
add_subdirectory(lib)
add_subdirectory(src)


