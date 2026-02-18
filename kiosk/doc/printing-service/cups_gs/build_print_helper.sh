#!/bin/bash

source /opt/fsl-imx-xwayland/6.6-scarthgap/environment-setup-armv8a-poky-linux

CUPS_INSTALL="$(pwd)/build_print_stack/install"

$CXX print_helper.cpp \
    -I${CUPS_INSTALL}/include \
    -L${CUPS_INSTALL}/lib64 \
    -lcups \
    -Wl,-rpath=/opt/print_stack/lib64 \
    -o print_helper

