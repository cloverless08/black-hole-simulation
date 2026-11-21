#!/bin/bash

rm -rf ./build
echo Removed build

cmake -B build -DCMAKE_BUILD_TYPE=Release -S .

cd ./build && make && cd ..
