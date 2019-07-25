# project(samples LANGUAGES CXX CUDA)
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

add_executable(keysSample keysSample.cpp)
add_executable(longKeysSample longKeysSample.cpp)

target_include_directories(keysSample PRIVATE ${CUDA_INCLUDE_DIRS})
target_include_directories(longKeysSample PRIVATE ${CUDA_INCLUDE_DIRS})

# Link CUDA dynamic library with our native CPP executables
# The executables depend on flavors_lib, so CMake will automatically include the same 
# header files that are used to compile flavors_lib, due to target_include_directories() called with PUBLIC
# in the flavors_lib project
target_link_libraries(keysSample flavors_lib ${CUDART_LIBRARY})
target_link_libraries(longKeysSample flavors_lib ${CUDART_LIBRARY})