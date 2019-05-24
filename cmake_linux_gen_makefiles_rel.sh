#!/bin/bash
GEN="Unix Makefiles"
mkdir build_makefiles_rel
cd build_makefiles_rel
cmake -D CMAKE_BUILD_TYPE=Release -G $(GEN) ..
cd ..