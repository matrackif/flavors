cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

find_library(CUDART_LIBRARY cudart ${CUDA_LINK_DIRECTORIES})

add_executable(benchmarks
	benchmark.cpp
	benchmark.h
	dictionary.cpp
	dictionary.h
	hostBenchmark.h
	ip.cpp
	ip.h
	runMain.cpp
	words.cpp
	words.h
)

target_include_directories(benchmarks PRIVATE ${CUDA_INCLUDE_DIRECTORIES} "${CMAKE_CURRENT_LIST_DIR}")

# Link CUDA dynamic library with our native CPP executables
# The executables depend on flavors_lib, so CMake will automatically include the same 
# header files that are used to compile flavors_lib, due to target_include_directories() called with PUBLIC
# in the flavors_lib project
target_link_libraries(benchmarks flavors_lib ${CUDART_LIBRARY})