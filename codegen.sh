#!/bin/bash

cd lib/virtual-network-interface/codegen/cpp
cmake .
make
cd ../../../../

lib/virtual-network-interface/codegen/cpp/vnicppcodegen lib/virtual-network-layers-cpp/interface interface/

