#!/bin/bash

cd linux-imx/

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0001-gpio-pca953x-fix-pca953x_irq_bus_sync_unlock-race.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0002-arm64-dts-add-i.MX93-11x11-FRDM-basic-support.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0003-arm64-dts-add-imx93-11x11-frdm-mt9m114-dts.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0004-Add-DSI-Panel-for-imx93.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0005-Add-CTP-support-for-waveshare-panel.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0006-arm64-dts-add-imx93-11x11-frdm-tianma-wvga-panel-dts.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0007-arm64-dts-add-imx93-11x11-frdm-aud-hat-dts.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0008-arm64-dts-add-button-support.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0009-arm64-dts-add-imx93-11x11-frdm-ov5640-dts.patch

#cd linux-imx/

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0010-arm64-dts-add-imx93-11x11-frdm-ld.dts-for-lpm.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0011-arm64-dts-add-pwm-function-of-the-LED.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0012-arm64-dts-add-imx93-11x11-frdm-8mic.dts.patch

git apply ../meta-imx-frdm/meta-imx-bsp/recipes-kernel/linux/linux-imx/0013-arm64-dts-add-imx93-11x11-frdm-lpuart.dts.patch
