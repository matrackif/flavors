
add_library(flavors_lib STATIC
  configuration.cu
  configuration.h
  containers.h
  dataInfo.cu
  dataInfo.h
  keys.cu
  keys.h
  masks.cu
  masks.h
  tree.cu
  tree.h
  utils.cu
  utils.h
  )
# This exports the include files to all targets dependent on flavors_lib
target_include_directories(flavors_lib PUBLIC "${CMAKE_CURRENT_LIST_DIR}") 

# target_compile_features(flavors_lib PUBLIC cxx_std_11) TODO, does it have to be C++11 only?

# We need to explicitly state that we need all CUDA files in the 
# particle library to be built with -dc as the member functions 
# could be called by other libraries and executables
set_target_properties( flavors_lib
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON)