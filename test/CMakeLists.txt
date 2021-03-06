cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

add_executable(tests
	helpers.cpp
	helpers.h
	runTests.cpp
	testConfiguration.cpp
	testKeys.cpp
	testLoad.cpp
	testMasks.cpp
	testTree.cpp
	testUtils.cpp
)

target_include_directories(tests PRIVATE ${CUDA_INCLUDE_DIRS} "${CMAKE_CURRENT_LIST_DIR}")

# Link CUDA dynamic library with our native CPP executables
# The executables depend on flavors_lib, so CMake will automatically include the same 
# header files that are used to compile flavors_lib, due to target_include_directories() called with PUBLIC
# in the flavors_lib project
target_link_libraries(tests flavors_lib ${CUDART_LIBRARY})