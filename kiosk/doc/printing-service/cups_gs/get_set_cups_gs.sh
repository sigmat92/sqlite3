#!/bin/bash
set -e

########################################
# CONFIG
########################################

SDK_PATH="/opt/fsl-imx-xwayland/6.6-scarthgap/environment-setup-armv8a-poky-linux"
JOBS=$(nproc)

WORK_DIR=$PWD/build_print_stack
SRC_DIR=$WORK_DIR/src
INSTALL_DIR=$WORK_DIR/install

CUPS_VERSION="2.4.10"
CUPS_TAR="cups-${CUPS_VERSION}-source.tar.gz"
CUPS_URL="https://github.com/OpenPrinting/cups/releases/download/v${CUPS_VERSION}/${CUPS_TAR}"

GS_VERSION="10.03.1"
GS_SHORT="10031"
GS_TAR="ghostpdl-${GS_VERSION}.tar.gz"
GS_URL="https://github.com/ArtifexSoftware/ghostpdl-downloads/releases/download/gs${GS_SHORT}/${GS_TAR}"

########################################
# PREPARE
########################################

echo "Loading Yocto SDK..."
source "$SDK_PATH"

mkdir -p "$SRC_DIR"
mkdir -p "$INSTALL_DIR"

cd "$SRC_DIR"

########################################
# DOWNLOAD CUPS
########################################

if [ ! -f "$CUPS_TAR" ]; then
    echo "Downloading CUPS $CUPS_VERSION..."
    wget "$CUPS_URL"
fi

########################################
# DOWNLOAD GHOSTSCRIPT
########################################

if [ ! -f "$GS_TAR" ]; then
    echo "Downloading Ghostscript $GS_VERSION..."
    wget "$GS_URL"
fi
########################################
# BUILD GHOSTSCRIPT
########################################

echo "Extracting Ghostscript..."
tar xf "$GS_TAR"

cd "ghostpdl-$GS_VERSION"

echo "Configuring Ghostscript..."
./configure \
    --host=aarch64-poky-linux \
    --prefix="$INSTALL_DIR" \
    --without-x \
    --disable-gtk \
    --disable-fontconfig

echo "Building Ghostscript..."
make -j$JOBS
make install

cd "$SRC_DIR"

########################################
# BUILD CUPS
########################################

echo "Extracting CUPS..."
tar xf "$CUPS_TAR"

cd "cups-$CUPS_VERSION"

echo "Configuring CUPS..."
./configure \
    --host=aarch64-poky-linux \
    --prefix="$INSTALL_DIR" \
    --disable-systemd \
    --disable-dbus \
    --without-ssl

echo "Building CUPS..."
make -j$JOBS
make install

########################################
# DONE
########################################

echo ""
echo "=========================================="
echo "Build Complete!"
echo "Install directory:"
echo "$INSTALL_DIR"
echo "=========================================="

