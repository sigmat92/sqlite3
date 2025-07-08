#!/bin/bash

QT_PREFIX_PATH=/home/prakash/Qt/6.5.3/gcc_64

rm -rf build
mkdir -p build && cd build

cmake .. -DCMAKE_PREFIX_PATH=$QT_PREFIX_PATH
make

