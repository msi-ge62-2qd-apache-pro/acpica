#!/bin/bash
# Copyright (C) 2017 ARM Ltd.
# SPDX-License-Identifier: BSD-3-Clause

export CROSS_COMPILE=aarch64-linux-gnu-
export BL33=`pwd`/edk2/Build/ArmVExpress-FVP-AArch64/RELEASE_GCC49/FV/FVP_AARCH64_EFI.fd

cd arm-trusted-firmware
make realclean
make DEBUG=1 PLAT=fvp SDEI_SUPPORT=1 fip all
