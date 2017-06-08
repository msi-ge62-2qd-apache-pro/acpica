#!/bin/bash
# Copyright (C) 2017 ARM Ltd.
# SPDX-License-Identifier: BSD-3-Clause

set -e

if [ $EUID -gt 0 ]; then
	echo "Not root? This won't work"
fi

truncate filesystem.img --size 10G
parted --script ./filesystem.img mklabel gpt
parted --script ./filesystem.img mkpart primary fat32 0 100MB
parted --script ./filesystem.img set 1 boot on
parted --script ./filesystem.img name 1 "EFI"
parted --script ./filesystem.img mkpart primary ext3 100MB 10GB
parted --script ./filesystem.img name 2 "Linux"

losetup -P -f ./filesystem.img

LOOPDEV=`losetup -a | grep "filesystem\.img" | tail -n 1 | cut -d : -f 1`

EFIPART=${LOOPDEV}p1
FSPART=${LOOPDEV}p2

mkdir mnt || true
mkfs.vfat -F 32 ${EFIPART}
fsck.msdos ${EFIPART}
mount -t vfat ${EFIPART} ./mnt

echo "MangleHEST.efi" > ./mnt/startup.nsh
echo "Image earlycon=pl011,0x1c090000 efi=debug root=/dev/vda2 rw" >> ./mnt/startup.nsh


cp ./edk2/Build/ArmVExpress-FVP-AArch64/RELEASE_GCC49/AARCH64/MangleHEST.efi ./mnt/
cp ./linux/arch/arm64/boot/Image ./mnt

umount ./mnt

mkfs.ext3 ${FSPART}
mount -t ext3 ${FSPART} ./mnt

tar zxf linaro-jessie-developer-20161006-97.tar.gz --strip-components=1 -C ./mnt

cp print_my_pa/print_my_pa ./mnt/root/

# Try and convince systemd to use the serial console
cat >> ./mnt/lib/systemd/system/ttyAMA0.service << EOF
[Unit]
Description=Serial Console Service

[Service]
ExecStart=/sbin/getty -L 115200 ttyAMA0 vt102
Restart=always

[Install]
WantedBy=multi-user.target
EOF

F=`mktemp rclocal.XXXXXX`
cat ./mnt/etc/rc.local | grep -v "exit" > ${F}
echo "systemctl daemon-reload" >> ${F}
echo "systemctl enable ttyAMA0" >> ${F}
echo "systemctl start ttyAMA0" >> ${F}
echo "exit 0" >> ${F}
cat ${F} > ./mnt/etc/rc.local
rm ${F}


# unlock root's account ...
sed -i 's/root:\*:/root::/gi' ./mnt/etc/shadow

umount ./mnt

losetup -d ${LOOPDEV}

chmod 0666 filesystem.img
