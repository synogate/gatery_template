#!/bin/sh

# todo: I need to update the docker image
vcpkg install boost-flyweight

git submodule update --init --recursive
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE:STRING=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake -DBoost_NO_WARN_NEW_VERSIONS=1
make -j 2