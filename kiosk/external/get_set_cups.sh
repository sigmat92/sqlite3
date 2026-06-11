#!/bin/bash

#Step 1 — Clone CUPS
rm -rf cups

git clone \
    --branch v2.4.10 \
    --single-branch \
    https://github.com/OpenPrinting/cups.git

cd cups
#Step 2 — Configure

#For native Ubuntu x86_64:

#./configure \
#    --disable-webif \
#    --disable-systemd \
#    --disable-avahi \
#    --without-tls

#For ARM64 cross compile:

./configure \
    --host=aarch64-linux-gnu \
    --disable-webif \
    --disable-systemd \
    --disable-avahi \
    --without-tls
#Step 3 — Build only libraries
make libs

#or simply:

#make -j8

#This generates:

#cups/libcups.a
#cups/libcups.so

#cups/filter/libcupsimage.a
#cups/filter/libcupsimage.so
#Step 4 — Verify raster header
#find . -name raster.h

#Expected:

#./cups/raster.h
#Step 5 — Verify raster symbols
#nm libcups.so | grep Raster

#Expected:

#cupsRasterOpen
#cupsRasterWriteHeader2
#cupsRasterWritePixels
#cupsRasterClose
