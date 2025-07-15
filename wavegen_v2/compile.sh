rm -rf build && mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$HOME/Qt/6.5.3/gcc_64
make -j$(nproc)

