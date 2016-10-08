#!/bin/bash

mkdir -p installs/bin
mkdir -p installs/lib

mkdir -p tmp
cd tmp
cmake ..
make -j `nproc`
cd ..

