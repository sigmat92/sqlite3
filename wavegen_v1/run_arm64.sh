#!/bin/bash

set -e

APP_NAME="WaveformGenerator"
BUILD_DIR="build_arm64"
QT_PLATFORM="eglfs"  # fallback: linuxfb
# Run the app
echo "[INFO] Running $APP_NAME..."
export QT_QPA_PLATFORM=$QT_PLATFORM
cd "$BUILD_DIR"
./$APP_NAME
