#!/bin/bash
GEN="Unix Makefiles"
mkdir build_makefiles_dbg
cd build_makefiles_dbg
cmake -D CMAKE_BUILD_TYPE=Debug -G $(GEN) ..
cd ..