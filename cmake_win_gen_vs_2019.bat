rem Run this file in a x64 Native Tools Command Prompt for VS on Windows
set GEN="Visual Studio 16 2019" 
mkdir build_vs_2019
cd build_vs_2019
cmake -D CUDA_INCLUDE_DIRS="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/include" -D CUDA_LINK_DIRS="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/lib/x64" -G %GEN% -A x64 ..
cd ..