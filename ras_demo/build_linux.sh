#!/bin/bash
# Copyright (C) 2017 ARM Ltd.
# SPDX-License-Identifier: BSD-3-Clause

export CROSS_COMPILE=aarch64-linux-gnu-
export ARCH=arm64

cd linux
make clean
make defconfig
./scripts/config -e CONFIG_ARM_SDE_INTERFACE
./scripts/config -e CONFIG_ACPI_APEI
./scripts/config -e CONFIG_ACPI_APEI_GHES
./scripts/config -e CONFIG_MEMORY_FAILURE
./scripts/config -e CONFIG_ACPI_APEI_MEMORY_FAILURE
./scripts/config -e CONFIG_HWPOISON_INJECT
make olddefconfig
make -j 8
