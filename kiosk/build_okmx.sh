#. /opt/fsl-imx-xwayland/6.6-scarthgap/environment-setup-armv8a-poky-linux
. /opt/fsl-imx-xwayland/6.1-mickledore/environment-setup-armv8a-poky-linux
rm -rf build_okmx
mkdir build_okmx && cd build_okmx
cmake .. -DCMAKE_TOOLCHAIN_FILE=$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake
cmake --build .

