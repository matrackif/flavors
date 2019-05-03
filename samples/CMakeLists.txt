# project(samples LANGUAGES CXX CUDA)
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

find_library(CUDART_LIBRARY cudart ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})

add_executable(keysSample keysSample.cpp)
add_executable(longKeysSample longKeysSample.cpp)

target_include_directories(keysSample PRIVATE ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
target_include_directories(longKeysSample PRIVATE ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

# Link CUDA dynamic library with our native CPP executables
# The executables depend on flavors_lib, so CMake will automatically include the same 
# header files that are used to compile flavors_lib, due to target_include_directories() called with PUBLIC
# in the flavors_lib project
target_link_libraries(keysSample flavors_lib ${CUDART_LIBRARY})
target_link_libraries(longKeysSample flavors_lib ${CUDART_LIBRARY})