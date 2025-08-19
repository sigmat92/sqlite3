How to enable rotary-encoder?

goto kernel path:

cd /home/prakash/yocto_scarthgap/imx-yocto-bsp/frdm-imx93_Kernel_build/tmp/work/imx93frdm-poky-linux/linux-imx/6.6.36+git/git

edit dts:

vim ~/yocto_scarthgap/imx-yocto-bsp/frdm-imx93_Kernel_build/tmp/work/imx93frdm-poky-linux/linux-imx/6.6.36+git/git/arch/arm64/boot/dts/freescale/imx93-11x11-frdm.dts

// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright 2024 NXP
 */

/dts-v1/;

#include <dt-bindings/usb/pd.h>
#include "imx93.dtsi"
#include "imx93-pinfunc.h"
&ele_fw2 {
	memory-region = <&ele_reserved>;
};

/ {
	model = "NXP i.MX93 11X11 FRDM board";
	compatible = "fsl,imx93-11x11-frdm", "fsl,imx93";

	chosen {
		stdout-path = &lpuart1;
	};
+/*added*/
+rotary@0 {
+        compatible = "rotary-encoder";
+        pinctrl-names = "default";
+        pinctrl-0 = <&rotary_encoder_pins>;
+        gpios = <&gpio2 18 GPIO_ACTIVE_LOW>,   /* OUTA: P11-12 */
+                <&gpio2 22 GPIO_ACTIVE_LOW>;   /* OUTB: P11-15 */
+        linux,axis = <0>;
+        rotary-encoder,relative-axis;
+        rotary-encoder,rollover;
+        rotary-encoder,steps-per-period = <4>;
+        debounce-interval = <2>;
+        wakeup-source;
+    };
+
+    rotary_sw: rotary-sw {
+        compatible = "gpio-keys";
+        pinctrl-names = "default";
+        pinctrl-0 = <&rotary_sw_pins>;
+        status = "okay";
 
+        button {
+            label = "Rotary Switch";
+            gpios = <&gpio2 17 GPIO_ACTIVE_LOW>;  /* SW: P11-11 */
+            linux,code = <28>; /* KEY_ENTER */
+            debounce-interval = <10>;
+        };
+    };
+/*added*/

...
...
...

+/*added*/
 	reserved-memory {
 		#address-cells = <2>;
 		#size-cells = <2>;
@@ -680,6 +708,23 @@ &tpm4 {
 };
 
 &iomuxc {
+/*added*/
+
+    rotary_encoder_pins: rotary-encoder-pins {
+        fsl,pins = <
+            MX93_PAD_GPIO_IO18__GPIO2_IO18  0x31  /* OUTA (P11-12) */
+            MX93_PAD_GPIO_IO22__GPIO2_IO22  0x31  /* OUTB (P11-15) */
+              
+        >;
+    };
+
+    rotary_sw_pins: rotary-sw-pins {
+        fsl,pins = <
+		MX93_PAD_GPIO_IO17__GPIO2_IO17  0x31  /* SW (P11-11) */ 
+        >;
+    };
+
+/*added*/
 	pinctrl_eqos: eqosgrp {
 		fsl,pins = <
 			MX93_PAD_ENET1_MDC__ENET_QOS_MDC			0x57e

..
..
..


Save and exit 

Create a .patch file

git checkout -b add_rotary_encoder
git add arch/arm64/boot/dts/freescale/imx93-11x11-frdm.dts
git commit -m "Add rotary encoder and push button  for i.MX93 FRDM"
git format-patch -1 HEAD

copy patch file to imx93frdm and apply patch

prakash@prakash-HP-ProBook-640-G2:~/yocto_scarthgap/imx-yocto-bsp/frdm-imx93_Kernel_build/tmp/work/imx93frdm-poky-linux/linux-imx/6.6.36+git/git$ cp 0001-Add-rotary-encoder-and-push-button-support-for-i.MX9.patch ~


prakash@prakash-HP-ProBook-640-G2:~/yocto_scarthgap/imx-yocto-bsp/sources/meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux$ ls
linux-imx  linux-imx_6.6.bbappend


edit linux-imx_6.6.bbappend

add at end
"
file://0001-Add-rotary-encoder-and-push-button-support-for-i.MX9.patch \
"

bitbake -c cleansstate virtual/kernel
bitbake virtual/kernel

copy driver on board

Check kernel driver loaded

dmesg | grep -i rotary


root@imx93frdm:~/rotary_encoder# evtest /dev/input/event3 
Input driver version is 1.0.1
Input device ID: bus 0x19 vendor 0x1 product 0x1 version 0x100
Input device name: "rotary-sw"
Supported events:
  Event type 0 (EV_SYN)
  Event type 1 (EV_KEY)
    Event code 28 (KEY_ENTER)
Properties:
Testing ... (interrupt to exit)
Event: time 1709187634.585955, type 1 (EV_KEY), code 28 (KEY_ENTER), value 1
Event: time 1709187634.585955, -------------- SYN_REPORT ------------
Event: time 1709187634.769108, type 1 (EV_KEY), code 28 (KEY_ENTER), value 0
Event: time 1709187634.769108, -------------- SYN_REPORT ------------
Event: time 1709187638.069603, type 1 (EV_KEY), code 28 (KEY_ENTER), value 1
Event: time 1709187638.069603, -------------- SYN_REPORT ------------
Event: time 1709187638.281603, type 1 (EV_KEY), code 28 (KEY_ENTER), value 0
Event: time 1709187638.281603, -------------- SYN_REPORT ------------
^C
root@imx93frdm:~/rotary_encoder# evtest /dev/input/event8 
Input driver version is 1.0.1
Input device ID: bus 0x19 vendor 0x0 product 0x0 version 0x0
Input device name: "rotary@0"
Supported events:
  Event type 0 (EV_SYN)
  Event type 2 (EV_REL)
    Event code 0 (REL_X)
Properties:
Testing ... (interrupt to exit)
Event: time 1709187656.389806, type 2 (EV_REL), code 0 (REL_X), value 1
Event: time 1709187656.389806, -------------- SYN_REPORT ------------
Event: time 1709187656.401793, type 2 (EV_REL), code 0 (REL_X), value 1
Event: time 1709187656.401793, -------------- SYN_REPORT ------------
Event: time 1709187658.430373, type 2 (EV_REL), code 0 (REL_X), value -1
Event: time 1709187658.430373, -------------- SYN_REPORT ------------
Event: time 1709187658.436923, type 2 (EV_REL), code 0 (REL_X), value -1
Event: time 1709187658.436923, -------------- SYN_REPORT ------------
