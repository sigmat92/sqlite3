rm -rf zxing-cpp
git clone --branch v1.4.0 --single-branch https://github.com/zxing-cpp/zxing-cpp.git
cd zxing-cpp
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
#cd /home/forlinx/sqlite3/kiosk/external/zxing-cpp
#mkdir -p build && cd build
# Ensure you are using a C++20 compiler as discussed previously
cmake -DCMAKE_CXX_STANDARD=20 ..
make ZXing  # This specific command will generate the headers
#make -j$(nproc)
#sudo make install
#sudo ldconfig
#This installs:
#/usr/local/include/ZXing/
#    BarcodeWriter.h
#    ReadBarcode.h
#    ImageView.h
#/usr/local/lib/libZXing.so
#/usr/local/lib/cmake/ZXing/ZXingConfig.cmake


