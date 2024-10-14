#!/bin/bash
# 
#
# Script for invoking CMake using the CMakeLists.txt file in this directory. 

set -e

# Standalone Kokkos

# following lines for build directory cleanup
find . ! -name '*.sh' -type f -exec rm -f {} +
find . -mindepth 1 -type d -exec rm -rf {} +

if spack find -p cmake; then
	cmake=$(spack location -i --first cmake)/bin/cmake
else
	cmake=cmake
fi

# Configure CMake with specified build type and other options
cmake_command="${cmake}"

# this will install in your build directory in a folder called install by default
INSTALL_PREFIX="./install" 

# Add the C++ compiler to the cmake command. There has got to be a better way to do this.
kokkos_compiler=$(spack find --show-full-compiler kokkos | grep kokkos | tail -n 1 | cut -d'%' -f2) || true
kokkos_cxx_path=$(spack compiler info "${kokkos_compiler}" | grep 'cxx' | awk '{print $3}' | grep -v '^$') || true

# optional CMake variables to pass in are PYTHON_PREFIX and PYTHON_EXECUTABLE
# if they are not passed in, then `which python` is called to determine your
# python executable, and from that sitepackages and libraries are inferred.
cmake_command+=" -D CMAKE_CXX_COMPILER=${kokkos_cxx_path}"
cmake_command+=" -D CMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}"
cmake_command+=" -D KokkosCore_PREFIX='../spack/opt/spack/linux-ubuntu22.04-zen2/gcc-11.4.0/kokkos-4.3.01-jrkk5qwkgxnxeljsjyylkfn75ibivquk/lib/cmake/Kokkos'"
cmake_command+=" -D KokkosKernels_PREFIX='../spack/opt/spack/linux-ubuntu22.04-zen2/gcc-11.4.0/kokkos-kernels-4.3.01-s5bhlul7uhm7mwyr6m2vznec5mucefab/lib/cmake/KokkosKernels'"
cmake_command+=" -D Compadre_USE_PYTHON:BOOL=OFF"
cmake_command+=" -D Compadre_EXAMPLES:BOOL=OFF"
cmake_command+=" -D Compadre_TESTS:BOOL=OFF"
cmake_command+=" -D CMAKE_BUILD_TYPE:STRING='Release'"
cmake_command+=" -D BUILD_SHARED_LIBS:BOOL=OFF"
cmake_command+=" ../compadre"

eval "${cmake_command}"

