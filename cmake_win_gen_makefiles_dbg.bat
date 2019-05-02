rem Run this file in a x64 Native Tools Command Prompt for VS on Windows
set GEN="Unix Makefiles" 
mkdir build_makefiles_dbg
cd build_makefiles_dbg
cmake -D CMAKE_BUILD_TYPE=Debug -G %GEN% ..
cd ..