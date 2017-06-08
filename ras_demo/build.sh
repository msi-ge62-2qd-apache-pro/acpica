#!/bin/bash
# Copyright (C) 2017 ARM Ltd.
# SPDX-License-Identifier: BSD-3-Clause

set -e

./build_acpica.sh
alias iasl="`pwd`/../generate/unix/bin/iasl"
./build_edk2.sh
./build_atf.sh
./build_linux.sh

# Build host/guest victim program
cd print_my_pa
make CC=aarch64-linux-gnu-gcc
cd ..

# retrieve a filesystem
wget -c https://releases.linaro.org/debian/images/developer-arm64/16.11/linaro-jessie-developer-20161006-97.tar.gz

