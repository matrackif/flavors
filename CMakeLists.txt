project(flavors LANGUAGES CXX CUDA)
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -arch=sm_50")

set(CUDA_INCLUDE_DIRECTORIES "${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}" CACHE STRING "Path to CUDA include directories")
message(STATUS "Set CUDA_INCLUDE_DIRECTORIES to: ${CUDA_INCLUDE_DIRECTORIES}")
set(CUDA_LINK_DIRECTORIES "${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES}" CACHE STRING "Path to CUDA static libraries")
message(STATUS "Set CUDA_LINK_DIRECTORIES to: ${CUDA_LINK_DIRECTORIES}")

find_package(Boost REQUIRED) # Need to set BOOST_ROOT environment variable
# Find Boost headers only
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# Common include directories for all projects
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/lib/cuda-api-wrappers)

add_subdirectory(flavors)
add_subdirectory(samples)
add_subdirectory(benchmarks)
add_subdirectory(test)