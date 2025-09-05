#readme
  mkdir -p /home/forlinx/ok-mx93
  
  mv OKMX93-linux-sdk.tar.bz2 ok-mx93/
  
  cd ok-mx93/
  
  cat sdk_md5.txt 
  
  md5sum OKMX93-linux-sdk.tar.bz2
  cat sdk_md5.txt 
  tar -xvf OKMX93-linux-sdk.tar.bz2
  
  forlinx@ubuntu:~/ok-mx93/OKMX93-linux-sdk$ ls
appsrc                               images
build.sh                             OKMX93-linux-fs-6.1.36
environment-setup-aarch64-toolchain  OKMX93-linux-kernel-6.1.36
extra                                tools
forlinx@ubuntu:~/ok-mx93/OKMX93-linux-sdk$ . environment-setup-aarch64-toolchain 
forlinx@ubuntu:~/ok-mx93/OKMX93-linux-sdk$ ./build.sh --help
Usage:
	./build.sh all              - build all
	./build.sh uboot            - only build uboot
	./build.sh kernel           - only build kernel
	./build.sh extra            - only build extra
	./build.sh ramdisk          - only build ramdisk
	./build.sh mkfs             - only build mkfs
	./build.sh apps             - only build apps
	./build.sh clean            - clean all
	./build.sh clean_uboot      - clean uboot
	./build.sh clean_kernel     - clean kernel
	./build.sh clean_apps       - clean apps
	./build.sh help             - print usage
	. environment-setup-aarch64-toolchain                  - set env

Execute the full compile command:
forlinx@ubuntu:~/ok-mx93/OKMX93-linux-sdk $ ./build.sh all
After the compilation is complete, the image files will be generated in the "images" directory.
forlinx@ubuntu:~/ok-mx93/OKMX93-linux-sdk/images$ tree
├── Image
├── OK-MX93-C.dtb
├── ok-mx93-linux-fs.sdcard.aa
├── ok-mx93-linux-fs.sdcard.ab
├── ok-mx93-linux-fs.sdcard.ac
├── ok-mx93-uboot.bin
├── ramdisk.img.gz
├── rootfs.bin
└── uboot
├── bl31.bin
├── fw_printenv
├── ok-mx93-uboot-a0.bin
├── ok-mx93-uboot-a1.bin
├── u-boot.bin
├── u-boot-spl-a0.bin
└── u-boot-spl-a1.bin
1 directory, 15 file


root@ok-mx93:/usr/bin# ./fltest_wifi.sh -i wlan0 -s Airtel_prak_6498 -p air63889

vi /etc/autorun.sh
#! /bin/sh
# qt env
. /etc/profile.d/weston.sh
. /etc/profile.d/qt6.sh
/usr/bin/weston-calibrate.sh
# user command
/root/start_wifi.sh

/root/cutecom-serial

exit 0

enable rotary encoder

change dts
compile kernel
copy dtb on board
compile kernel module copy on board
compile qt app copy executable on board
insert kernel module
dmesg | grep rotary
2 inputs and 1 gray
run qt app RotaryTestApp roatate and press knob

