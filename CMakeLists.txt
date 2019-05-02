project(flavors LANGUAGES CXX CUDA)
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -arch=sm_50")

message(STATUS " CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES: ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}")
message(STATUS " CMAKE_CUDA_FLAGS: ${CMAKE_CUDA_FLAGS}")

find_package(Boost REQUIRED) # Need to set BOOST_ROOT environment variable

# Find Boost headers only TODO move this to test/CMakeLists.txt since only it uses Boost
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