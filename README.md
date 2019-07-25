![alt text](https://www.iconsdb.com/icons/download/guacamole-green/ice-cream-2-48.png)
flavors
=======

Flavors is library of GPU Trie structures for fast parallel lookup. It provides facilities to build Tries with changing bit stride and search them on the GPU. 


### Build
This repository contains
* CUDA static library called (`flavors` module), in which the Trie data structure is implemented. 
* `keysSample` executable which will run a sample of reshaping keys according to a trie configuration
* `longKeysSample` executable does the same thing as above but with longer keys
* `tests` executable that runs unit tests on the various classes implemented in this repository (Tree, Keys, etc)
* `benchmarks` executable that collects various statistics such as execution time of various algorithms and outputs the results to a .csv file.
#### Dependencies
* CUDA Toolkit installed (tested with version 10.1). https://docs.nvidia.com/cuda/index.html#
* Nvidia GPU with compute capability sm_52 or higher (Maxwell/GeForce 900 series).
* Boost C++ libraries https://www.boost.org/ (tested with version 1.70). Path to the Boost libraries must be set in the environment variable *BOOST_ROOT*
* CMake version 3.9 or higher (tested with version 3.15) https://cmake.org/download/
* C++ compiler (tested with Visual Studio's cl.exe 19.16.27032.1 for x64)

#### Important notes
The executables have been tested to work on the configuration above on Windows 10 64 bit. All components of the application are intented to be built in 64 bit release mode, any other configuration may cause crashes or undefined behavior. 

#### Generate makefiles using CMake

```
mkdir build_makefiles_rel
cd build_makefiles_rel
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release ..
```
##### Compile modules using makefile
```
#To build all modules
make (option -j8 is recommended if possible)

#To build flavors CUDA static library
make flavors

#To build benchmarks
make benchmarks

#To build samples 
make samples
OR one can build both samples separately
make keysSample
make longKeysSample 

#To build tests
make tests
```
*Note: tests seem to only work when they are compiled in the `Release` configuration.*
Or run the provided convenience script `cmake_win_gen_makefiles_rel.bat` on Windows
*Note: When generating makefiles CMake looks for CUDA include files/static libs in the default location, in certain cases one may need to pass the paths to those locations manually as described below...*
#### Generate Visual Studio 2017 solution using CMake

```
mkdir build_vs_2017
cd build_vs_2017
cmake -D CUDA_INCLUDE_DIRS=<PATH_TO_CUDA_INCLUDE_DIRECTORIES> -D CUDA_LINK_DIRS=<PATH_TO_CUDA_STATIC_LIB_DIRECTORIES> -G "Visual Studio 15 2017"  -A x64 ..
```
Or run the provided convenience script `cmake_win_gen_vs_2017.bat` on Windows. *Note: it assumes that one has CUDA 10.1 installed in the default location*.

* Example location of CUDA_INCLUDE_DIRS: `C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/include`
* Example location of CUDA_LINK_DIRS: `C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/lib/x64`


### Where to go next?

#### Getting started

For getting started guide go to samples [page](samples/README.md).

#### Benchmarks

More information about how to run benchmarks and some experimental results can be found on [this](benchmarks/README.md) page.
