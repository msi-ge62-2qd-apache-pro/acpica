#!/bin/bash
# Copyright (C) 2017 ARM Ltd.
# SPDX-License-Identifier: BSD-3-Clause

CROSS_COMPILE=aarch64-linux-gnu-
CC_PATH=`which ${CROSS_COMPILE}gcc`
EDK2_DSC=OpenPlatformPkg/Platforms/ARM/VExpress/ArmVExpress-FVP-AArch64.dsc

cd edk2
. edksetup.sh
make -C BaseTools clean
make -C BaseTools

export GCC49_AARCH64_PREFIX=`dirname ${CC_PATH}`/${CROSS_COMPILE}
make -f ArmPlatformPkg/Scripts/Makefile EDK2_ARCH=AARCH64 EDK2_DSC=${EDK2_DSC} EDK2_BUILD=RELEASE EDK2_TOOLCHAIN=GCC49 EDK2_MACROS="-n 6 -D ARM_FOUNDATION_FVP=1"
