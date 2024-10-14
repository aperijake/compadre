#!/bin/bash
# 
#
# Script for invoking CMake using the CMakeLists.txt file in this directory. 


# Standalone Kokkos

# following lines for build directory cleanup
find . ! -name '*.sh' -type f -exec rm -f {} +
find . -mindepth 1 -type d -exec rm -rf {} +

# make sure you installed kokkos somewhere before setting this
# see doc/Kokkos-Install.md for details on installing Kokkos
MY_KOKKOSCORE_PREFIX="FILEPATH=$(spack location -i kokkos)/lib/cmake/Kokkos"

# pick your favorite c++ compiler
MY_CXX_COMPILER=`which g++`

# this will install in your build directory in a folder called install by default
INSTALL_PREFIX="./install" 

# Add the C++ compiler to the cmake command. There has got to be a better way to do this.
kokkos_compiler=$(spack find --show-full-compiler kokkos | grep kokkos | tail -n 1 | cut -d'%' -f2) || true
kokkos_cxx_path=$(spack compiler info "${kokkos_compiler}" | grep 'cxx' | awk '{print $3}' | grep -v '^$') || true

# optional CMake variables to pass in are PYTHON_PREFIX and PYTHON_EXECUTABLE
# if they are not passed in, then `which python` is called to determine your
# python executable, and from that sitepackages and libraries are inferred.
cmake \
    -D CMAKE_CXX_COMPILER="$kokkos_cxx_path" \
    -D CMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" \
    -D KokkosCore_PREFIX="../spack/opt/spack/darwin-sequoia-m1/apple-clang-16.0.0/kokkos-4.4.01-of5afuwcy6mcaluhid2wir5ct4ovwvcw/lib/cmake/Kokkos" \
    -D KokkosKernels_PREFIX="../spack/opt/spack/darwin-sequoia-m1/apple-clang-16.0.0/kokkos-kernels-4.4.01-sp2a2b27xds6b7kcqfhuekzshd3xckfm/lib/cmake/KokkosKernels" \
    -D Compadre_USE_PYTHON:BOOL=OFF \
    -D Compadre_EXAMPLES:BOOL=OFF \
    -D Compadre_TESTS:BOOL=OFF \
    -D CMAKE_BUILD_TYPE:STRING="Release" \
    ../compadre
    # -D Kokkos_DIR="$MY_KOKKOSCORE_PREFIX" \
    # -D BUILD_SHARED_LIBS:BOOL=OFF \
    # -D Compadre_USE_MPI:BOOL=ON \
    # -D CMAKE_CXX_COMPILER="$MY_CXX_COMPILER" \
