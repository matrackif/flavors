![alt text](https://www.iconsdb.com/icons/download/guacamole-green/ice-cream-2-48.png)
flavors
=======

Flavors is library of GPU Trie structures for fast parallel lookup. It provides facilities to build Tries with changing bit stride and search them on the GPU.



### Building

#### Generate makefiles using CMake

```
mkdir build_makefiles_rel
cd build_makefiles_rel
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release ..
```
Or run the provided convenience script `cmake_win_gen_makefiles_rel.bat` on Windows
*Note: When generating makefiles CMake looks for CUDA include files/static libs in the default location, in certain cases one may need to pass the paths to those locations manually as described below...*
#### Generate Visual Studio 2017 solution using CMake

```
mkdir build_vs_2017
cd build_vs_2017
cmake -D CUDA_INCLUDE_DIRECTORIES=<PATH_TO_CUDA_INCLUDE_DIRECTORIES> -D CUDA_LINK_DIRECTORIES=<PATH_TO_CUDA_STATIC_LIB_DIRECTORIES> -G "Visual Studio 15 2017"  -A x64 ..
```
Or run the provided convenience script `cmake_win_gen_vs_2017.bat` on Windows. *Note: it assumes that one has CUDA 10.1 installed in the default location*.

* Example location of CUDA_INCLUDE_DIRECTORIES: `C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/include`
* Example location of CUDA_LINK_DIRECTORIES: `C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/lib/x64`

```
#To build all modules
make (option -j4 is recommended)

#To build flavors CUDA static library
make flavors

#To build benchmarks
make benchmarks

#To build samples
make samples

#To build tests
make test
```
*Note: tests seem to only work when they are compiled in the `Release` configuration.*

### Dependencies
The `test` project requires the Boost C++ library, the CMake script looks for Boost using the `BOOST_ROOT` environment variable. It should be set.

### Where to go next?

#### Getting started

For getting started guide go to samples [page](samples/README.md).

#### Benchmarks

More information about how to run benchmarks and some experimental results can be found on [this](benchmarks/README.md) page.
