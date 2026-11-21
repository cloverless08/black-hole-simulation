#!/bin/bash

rm -rf ./build
echo Removed build

cmake -B build -DCMAKE_BUILD_TYPE=Release -S .
echo Compiled makefiles for application into ./build with type: Release

cd ./build && make && cd ..
echo Built application in ./build
