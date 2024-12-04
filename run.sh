#!/bin/bash

set -e

mkdir -p ./build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build 
./build/willow-bird
