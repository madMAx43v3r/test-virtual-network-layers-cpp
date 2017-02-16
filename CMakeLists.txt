cmake_minimum_required(VERSION 2.4)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -O3 -pthread -Wfatal-errors")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/installs/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/installs/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/installs/bin)

add_subdirectory(lib)

include_directories(
	generated/include/
	lib/virtual-network-layers-cpp/include/
)

include(generated/vni_input_output.cmake)
add_library(vni ${VNI_OUTPUT_FILES_SOURCE})

add_subdirectory(src)


