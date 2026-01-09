. /opt/fsl-imx-xwayland/6.6-scarthgap/environment-setup-armv8a-poky-linux
mkdir build_arm && cd build_arm
cmake .. -DCMAKE_TOOLCHAIN_FILE=$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake
cmake --build .

