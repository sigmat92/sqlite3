#! /bin/sh
SHELL_PATH="$(cd "$(dirname "$0")"; pwd)"
cd $SHELL_PATH
rm -f ./installer_i386
sudo apt-get install libglib2.0-dev
sudo apt-get install libgtk+2.0-dev

gcc installer.c -o installer_i386 -m32 `pkg-config --cflags --libs glib-2.0 gtk+-2.0`
