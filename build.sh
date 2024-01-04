#!/bin/bash

# cmake_code/Class_1/08/math/build.sh
set -e	//任何一行命令失败则停止
cmake -S ./src -B ./build 
cd build
make -j 4
