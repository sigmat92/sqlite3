#!/bin/bash

QT_PATH=/home/prakash/Qt/6.5.3/gcc_64

rm -rf build
mkdir -p build && cd build

cmake .. -DCMAKE_PREFIX_PATH=$QT_PATH
make -j$(nproc)

echo -e "\nBuild complete! Run with: ./build/QtQuickApp"

