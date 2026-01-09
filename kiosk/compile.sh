#!/bin/bash

QT_PATH="/home/prakash/Qt/6.5.3/gcc_64"
BUILD_DIR="build"

rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR

cmake .. -DCMAKE_PREFIX_PATH="$QT_PATH/lib/cmake"
cmake --build . -- -j$(nproc)


