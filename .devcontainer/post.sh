#!/bin/sh
git submodule update --init --recursive
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE:STRING=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake
make -j 2