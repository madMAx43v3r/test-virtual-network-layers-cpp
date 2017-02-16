#!/bin/bash

cd lib/virtual-network-interface
./build_all.sh
cd ../..

./lib/virtual-network-interface/vnicppcodegen -x lib/virtual-network-layers-cpp/interface interface/

