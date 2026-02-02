# Install script for directory: /home/prakash/sqlite3/kiosk/external/zxing-cpp/core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/fsl-imx-xwayland/6.6-scarthgap/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/libZXing.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ZXing" TYPE FILE FILES
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/BarcodeFormat.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/BitHacks.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ByteArray.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/CharacterSet.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/CharacterSetECI.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Flags.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/GTIN.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/TextUtfEncoding.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ZXAlgorithms.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ZXConfig.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Content.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/DecodeHints.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/DecodeStatus.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Error.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ImageView.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Point.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Quadrilateral.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ReadBarcode.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Result.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/StructuredAppend.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/BitMatrix.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/BitMatrixIO.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Matrix.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/MultiFormatWriter.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ZXing" TYPE FILE FILES "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/ZXVersion.h")
endif()

