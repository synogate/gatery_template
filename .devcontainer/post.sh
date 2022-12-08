#!/bin/sh
git submodule update --init --recursive
premake5 gmake2
make -j 2