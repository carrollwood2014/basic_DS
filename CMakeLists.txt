cmake_minimum_required(VERSION 3.6)

project(basic_DS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build_outputs/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(binomial_heap)
add_subdirectory(heap_related)