#!/usr/sh
git submodule update --init --recursive
tools/premake5 gmake2
make