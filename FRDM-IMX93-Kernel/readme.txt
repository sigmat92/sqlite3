How to compile Linux Kernel Image and device tree using Yocto SDK


This guide walks you through setting up and building the Yocto SDK, customizing a device tree (DTS), and compiling the kernel for NXP i.MX platforms. It is designed to simplify the process, from downloading tools to creating functional images for embedded devices.


Prerequisites

Required Software:

A Linux-based operating system (Ubuntu/Debian recommended).

Git installed (sudo apt install git).

Yocto dependencies:
$ sudo apt install gawk wget git diffstat unzip texinfo gcc build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 python3-subunit zstd liblz4-tool file locales libacl1

Hardware:

An NXP i.MX-based development board (i.MX6, i.MX7, i.MX8, or i.MX9).
Sufficient storage space
 

1. Downloading the Repository

Start by downloading the necessary tools and repository. If the ~/bin folder does not already exist, create it:

$ mkdir ~/bin (this step may not be needed if the bin folder already exists)
$ curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
$ chmod a+x ~/bin/repo
$ export PATH=~/bin:$PATH
 

2. Compile the Yocto SDK:


Create and navigate to a release directory:

$: mkdir <release>
$: cd <release>
 

Initialize and sync the repo:

$: repo init -u https://github.com/nxp-imx/imx-manifest -b <branch name> [ -m <release manifest>]
$: repo sync
 

Set up the environment and build the SDK:

$: [MACHINE=<machine>] [DISTRO=fsl-imx-<backend>] source ./imx-setup-release.sh -b bld-<backend>
$: bitbake <image recipe> -c populate_sdk
 

Example:

$: mkdir Yocto_SDK
$: cd Yocto_SDK
$: repo init -u https://github.com/nxp-imx/imx-manifest -b imx-linux-scarthgap -m imx-6.6.52-2.2.0.xml
$: repo sync

$: MACHINE=imx93evk DISTRO=fsl-imx-xwayland source ./imx-setup-release.sh -b bld-xwayland
$: bitbake imx-image-full -c populate_sdk
 

Recommendation: Use the full image (imx-image-full) to include all available packages and libraries.

 

Run the generated .sh file to install the SDK:

sudo ./fsl-imx-xwayland-glibc-x86_64-imx-image-full-armv8a-imx93evk-toolchain-6.6-scarthgap.sh
 

The final .sh file is located in:

bld-xwayland/tmp/deploy/sdk/
 

3. Cloning the Kernel Repository (linux-imx repository)

 

Clone the kernel source matching the version of the Yocto SDK you built earlier:

 

$: git clone https://github.com/nxp-imx/linux-imx.git -b <Kernel-version>
 

EXAMPLE:

$: git clone https://github.com/nxp-imx/linux-imx.git -b lf-6.6.52-2.2.0
 

4. Customizing the Device Tree

Device trees can be modified or created based on your hardware setup.

 

Device Tree Locations:

 

iMX6 and iMX7:

arch/arm/boot/dts/nxp/imx/
 

iMX8 and iMX9:

arch/arm64/boot/dts/freescale/
 

If you create a new device tree, add it to the respective Makefile:

 

iMX8 and iMX9:

arch/arm64/boot/dts/freescale/Makefile
 

iMX6 and iMX7:

arch/arm/boot/dts/nxp/imx/Makefile
 

 

5. Setting Up the Cross-Compilation Environment

To prepare for kernel compilation, source the environment setup script. Assuming the Yocto SDK is installed in /opt, run:

 

EXAMPLE:

$ source /opt/fsl-imx-xwayland/6.6-scarthgap/environment-setup-armv8a-poky-linux
 

6. Configuring the Kernel

Make configuration adjustments as needed:

 

iMX8 and iMX9:

arch/arm64/configs/imx_v8_defconfig
 

iMX6 and iMX7:

arch/arm/configs/imx_v7_defconfig
 

Use the appropriate configuration command:

 

iMX8 and iMX9:

$: make imx_v8_defconfig
 

iMX6 and iMX7:

$: make imx_v7_defconfig
 

7. Compiling Device Trees Only

 

To compile only the device tree files, run:

$: make dtbs
 

8. Compiling the Kernel

Finally, compile the kernel image using:

$ make -j $(nproc) 
 

The resulting kernel image will be located in:

iMX8 and iMX9:

arch/arm64/boot/
 

iMX6 and iMX7:

arch/arm/boot/
 

References:

IMX YOCTO PROJECT USERS GUIDE

IMX LINUX USERS GUIDE 

IMX REFERENCE MANUAL 

 
