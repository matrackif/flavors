rem Run this file in a x64 Native Tools Command Prompt for VS on Windows
set GEN="Unix Makefiles" 
mkdir build_makefiles_rel
cd build_makefiles_rel
cmake -G %GEN% -D CMAKE_BUILD_TYPE=Release ..
cd ..