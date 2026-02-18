#!/bin/bash
set -euo pipefail

########################################
# CONFIG
########################################

SDK_ENV="/opt/fsl-imx-xwayland/6.6-scarthgap/environment-setup-armv8a-poky-linux"
JOBS=$(nproc)

WORKDIR="$PWD/build_print_stack_minimal"
SRCDIR="$WORKDIR/src"
DESTDIR="$WORKDIR/stage"

PREFIX="/opt/print"

CUPS_VERSION="2.4.10"
GS_VERSION="10.03.1"
GS_SHORT="10031"

########################################
# LOAD YOCTO SDK
########################################

echo ">>> Loading Yocto SDK"
source "$SDK_ENV"

########################################
# CLEAN BUILD
########################################

rm -rf "$WORKDIR"
mkdir -p "$SRCDIR" "$DESTDIR"
cd "$SRCDIR"

########################################
# DOWNLOAD HELPER
########################################

fetch() {
    if [ ! -f "$2" ]; then
        echo "Downloading $2"
        wget --show-progress "$1" -O "$2"
    fi
}

########################################
# DOWNLOAD SOURCES
########################################

echo ">>> Downloading sources"

# CUPS
fetch \
https://github.com/OpenPrinting/cups/releases/download/v${CUPS_VERSION}/cups-${CUPS_VERSION}-source.tar.gz \
cups-${CUPS_VERSION}-source.tar.gz

# Ghostscript (OFFICIAL Artifex release location)
fetch \
https://github.com/ArtifexSoftware/ghostpdl-downloads/releases/download/gs${GS_SHORT}/ghostscript-${GS_VERSION}.tar.gz \
ghostscript-${GS_VERSION}.tar.gz

########################################
# BUILD GHOSTSCRIPT (MINIMAL, PCL ONLY)
########################################

echo ">>> Building Ghostscript (pxlmono only)"

tar xf ghostscript-${GS_VERSION}.tar.gz
cd ghostscript-${GS_VERSION}

./configure \
  --host=aarch64-poky-linux \
  --prefix=/usr \
  --disable-cups \
  --disable-gtk \
  --disable-x \
  --disable-dynamic \
  --disable-hidden-visibility \
  --without-fontconfig \
  --without-tesseract \
  --with-drivers=pxlmono

make -j${JOBS}
make DESTDIR="${DESTDIR}" install

cd "$SRCDIR"

########################################
# BUILD CUPS (RAW USB ONLY)
########################################

echo ">>> Building CUPS (RAW, libusb backend)"

tar xf cups-${CUPS_VERSION}-source.tar.gz
cd cups-${CUPS_VERSION}

./configure \
  --host=aarch64-poky-linux \
  --prefix=/usr \
  --sysconfdir=/etc \
  --localstatedir=/var \
  --disable-systemd \
  --disable-dbus \
  --disable-avahi \
  --enable-libusb \
  --disable-usblp \
  --without-pam \
  --without-php \
  --without-perl \
  --with-cups-user=lp \
  --with-cups-group=lp

make -j${JOBS}
make DESTDIR="${DESTDIR}" install

cd "$WORKDIR"

########################################
# RELOCATE INTO /opt/print
########################################

echo ">>> Creating /opt/print layout"

mkdir -p "${DESTDIR}${PREFIX}"

rsync -a "${DESTDIR}/usr/" "${DESTDIR}${PREFIX}/"
rsync -a "${DESTDIR}/etc/" "${DESTDIR}${PREFIX}/etc/"
rsync -a "${DESTDIR}/var/" "${DESTDIR}${PREFIX}/var/"

########################################
# ENVIRONMENT WRAPPER
########################################

cat > "${DESTDIR}${PREFIX}/env.sh" <<EOF
export PATH=${PREFIX}/bin:${PREFIX}/sbin:\$PATH
export LD_LIBRARY_PATH=${PREFIX}/lib
export CUPS_SERVERROOT=${PREFIX}/etc/cups
export CUPS_DATADIR=${PREFIX}/share/cups
export CUPS_STATEDIR=${PREFIX}/var/run/cups
export CUPS_CACHEDIR=${PREFIX}/var/cache/cups
export TMPDIR=/tmp
EOF

chmod +x "${DESTDIR}${PREFIX}/env.sh"

########################################
# CLEAN STAGING
########################################

rm -rf "${DESTDIR}/usr" "${DESTDIR}/etc" "${DESTDIR}/var"

########################################
# DONE
########################################

echo ""
echo "===================================================="
echo " MINIMAL EMBEDDED PRINT STACK BUILT"
echo ""
echo " Deploy:"
echo "   rsync -av ${DESTDIR}/ root@imx93:/"
echo ""
echo " On target:"
echo "   source /opt/print/env.sh"
echo "   cupsd &"
echo ""
echo " Create RAW printer (Pantum P2518):"
echo "   lpadmin -p pantum -E -v usb://Pantum/P2518 -m raw"
echo ""
echo " Test:"
echo "   echo 'PRINT OK' | lp -d pantum"
echo "===================================================="

