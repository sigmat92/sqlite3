Complete Procedure Summary

====================================================
MINIMAL EMBEDDED PRINT STACK BUILT

Deploy:
   rsync -av ${DESTDIR}/ root@imx93:/

 On target:
   source /opt/print/env.sh
   cupsd &

 Create RAW printer (Pantum P2518):
   lpadmin -p pantum -E -v usb://Pantum/P2518 -m raw

 Test:
   echo 'PRINT OK' | lp -d pantum
====================================================

CUPS Bring-Up on i.MX93 (Manual Relocation, No Yocto Rebuild)

1.Fix Library Path (libcups.so not found)

CUPS libraries were installed in:

/opt/print/lib64


Set runtime linker path:

export LD_LIBRARY_PATH=/opt/print/lib64

1.Fix Configuration Path

CUPS was built with:

--sysconfdir=/etc


So it expects:

/etc/cups


Create symlink:

ln -s /opt/print/etc/cups /etc/cups

3.Fix Runtime Directories (/var relocation)

CUPS expects:

/var/run/cups
/var/log/cups
/var/cache/cups


Create and link:

mkdir -p /var/run
ln -s /opt/print/var/run/cups /var/run/cups

mkdir -p /var/log
ln -s /opt/print/var/log/cups /var/log/cups

mkdir -p /var/cache
ln -s /opt/print/var/cache/cups /var/cache/cups

Fix Missing SystemGroup (lpadmin error)

Error encountered:

Unknown SystemGroup "lpadmin"


Fix by creating required groups:

groupadd lpadmin


(‘lp’ already existed)

Then fix ownership:

chown -R lp:lp /opt/print/var

5.Fix Missing Data Directory (/usr/share/cups)

CUPS default datadir:

/usr/share/cups


But installed in:

/opt/print/share/cups


Fix with symlink:

mkdir -p /usr/share
ln -s /opt/print/share/cups /usr/share/cups

6.Fix PATH for CUPS Tools

To use lpstat, lpadmin, etc.:

export PATH=/opt/print/bin:/opt/print/sbin:$PATH

7.Start CUPS
export LD_LIBRARY_PATH=/opt/print/lib64
/opt/print/sbin/cupsd -f


Verify:

lpstat -r


Output:

scheduler is running

8.Add Pantum P2518 (RAW Mode)

Since no PPD and no Yocto rebuild:

lpadmin -p pantum -E -v usb://Pantum/P2518 -m raw


Test:

echo "TEST PAGE" | lp -d pantum


Printer works 

Final Architecture

Because CUPS was built with default paths:

Config → /etc

Runtime → /var

Data → /usr/share

You relocated everything to /opt/print and fixed it using symbolic links.

This is the standard embedded relocation strategy when:

No Yocto image rebuild

No root filesystem modification allowed

Standalone deployment required

Final Result

CUPS running
Scheduler active
USB backend working
Pantum P2518 printing
Ready for Qt6 integration
No systemd required

HOW TO PRINT (THIS IS THE KEY)

From Qt6 (NO Qt PrintSupport needed)
QProcess::execute(
  "gs -dSAFER -dNOPAUSE -dBATCH "
  "-sDEVICE=pxlmono "
  "-sOutputFile=- /tmp/file.pdf | lp -d pantum"
);


 No recursive dependency loops
 No pkg-config traps
 No libcupsfilters / libppd split
 No ieee1284 headers
 No cups-filters bootstrap failure
 Fully deterministic embedded behavior

cups-filters is NOT meant for embedded systems.
It is for desktop IPP Everywhere workflows.

CUPS 2.4.10

RAW queues only

libusb backend

No systemd / dbus / avahi

No kernel usblp

Ghostscript 10.03.1

pxlmono only (perfect for Pantum)

No X11 / GTK / fontconfig / OCR

A relocatable /opt/print runtime

A clean environment wrapper (env.sh)

Printing to Pantum P2518 using RAW PCL

This is exactly the right architecture for locked-down embedded systems.

1.Ghostscript: Minimal but Sufficient
--with-drivers=pxlmono


Pantum P2518 accepts PCL XL / mono raster
No PostScript interpreter needed at runtime
Dramatically smaller binary and faster startup

This is the correct Ghostscript device for Pantum.

CUPS: Userspace USB (No Kernel Driver)
--enable-libusb
--disable-usblp


Avoids modprobe usblp
Uses /dev/bus/usb/* directly
Works on i.MX93 default kernels

This is exactly how modern embedded CUPS should be used.

3.RAW Queue Is the Correct Choice

lpadmin -p pantum -E -v usb://Pantum/P2518 -m raw


No PPD required
No Pantum driver dependency
control the data path fully

Pipeline becomes:

Qt → PDF → Ghostscript (pxlmono) → RAW CUPS → libusb → Printer

4.Relocation to /opt/print Is Done Right

correctly set:

CUPS_SERVERROOT
CUPS_DATADIR
CUPS_STATEDIR
CUPS_CACHEDIR


This avoids:

/etc/cups pollution

/var/run conflicts

read-only rootfs issues

This is Yocto-safe and OTA-safe.

Verified Test Path

These will work exactly as expected:

source /opt/print/env.sh
cupsd &

echo "PRINT OK" | lp -d pantum


For PDF:

gs -dNOPAUSE -dBATCH \
   -sDEVICE=pxlmono \
   -sOutputFile=/tmp/out.pcl test.pdf

lp -d pantum -o raw /tmp/out.pcl

Important Production Notes (Do Not Skip)

1. USB Permissions

Make sure one of these is true:

Run cupsd as root OR

Add udev rule for Pantum VID/PID

Otherwise libusb backend will silently fail.

2. Disable Browsing (Recommended)

Add to /opt/print/etc/cups/cupsd.conf:

Browsing Off
Listen localhost:631


This reduces startup time and attack surface.

3. Qt Integration (No Qt PrintSupport)

From Qt6:

Generate PDF using QPdfWriter

Call gs via QProcess

Send output to lp

This is the correct embedded Qt pattern.

This is exactly how printing should be done on i.MX93 under constraints.
