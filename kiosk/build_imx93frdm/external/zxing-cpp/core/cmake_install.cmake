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
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Barcode.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/BarcodeFormat.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/BitHacks.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ByteArray.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/CharacterSet.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Content.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Error.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Flags.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/GTIN.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ImageView.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Point.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Quadrilateral.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Range.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ReadBarcode.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ReaderOptions.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/StructuredAppend.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/TextUtfEncoding.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ZXingCpp.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ZXAlgorithms.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/ZXVersion.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/DecodeHints.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Result.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/BitMatrix.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/BitMatrixIO.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/Matrix.h"
    "/home/prakash/sqlite3/kiosk/external/zxing-cpp/core/src/MultiFormatWriter.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ZXing" TYPE FILE FILES "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/Version.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ZXing/ZXingTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ZXing/ZXingTargets.cmake"
         "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/CMakeFiles/Export/f9e04a807b27a41299a115186893fdf1/ZXingTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ZXing/ZXingTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ZXing/ZXingTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ZXing" TYPE FILE FILES "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/CMakeFiles/Export/f9e04a807b27a41299a115186893fdf1/ZXingTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ZXing" TYPE FILE FILES "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/CMakeFiles/Export/f9e04a807b27a41299a115186893fdf1/ZXingTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/zxing.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ZXing" TYPE FILE FILES
    "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/ZXingConfig.cmake"
    "/home/prakash/sqlite3/kiosk/build_imx93frdm/external/zxing-cpp/core/ZXingConfigVersion.cmake"
    )
endif()

