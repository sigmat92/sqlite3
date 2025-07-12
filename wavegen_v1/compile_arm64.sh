#!/bin/bash

set -e

APP_NAME="WaveformGenerator"
BUILD_DIR="build_arm64"
QT_PLATFORM="eglfs"  # fallback: linuxfb

echo "========== Qt6 Waveform Generator Build Script =========="

# Step 1: Set Qt6 path if needed
if [ -z "$CMAKE_PREFIX_PATH" ]; then
	    QT6_DIR=$(find /usr -type f -name Qt6Config.cmake 2>/dev/null | head -n1 | xargs dirname | xargs dirname)
	        if [ -n "$QT6_DIR" ]; then
			        export CMAKE_PREFIX_PATH="$QT6_DIR"
				        echo "[INFO] Using Qt6 path: $CMAKE_PREFIX_PATH"
					    else
						            echo "[WARNING] Qt6Config.cmake not found. Set CMAKE_PREFIX_PATH manually if build fails."
							        fi
fi

# Step 2: Clean previous build
echo "[INFO] Cleaning build directory..."
rm -rf "$BUILD_DIR"
mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

# Step 3: Run CMake
echo "[INFO] Configuring CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Step 4: Compile
echo "[INFO] Building $APP_NAME..."
make -j$(nproc)

# Step 5: Run the app
#echo "[INFO] Running $APP_NAME..."
#export QT_QPA_PLATFORM=$QT_PLATFORM
#./$APP_NAME

