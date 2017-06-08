#!/bin/bash
# Copyright (C) 2017 ARM Ltd.
# SPDX-License-Identifier: BSD-3-Clause

set +x
TREE=`pwd`
MODEL_PATH=/usr/local/models/current/
source ${HOME}/workspace/ModelShell_0.0/source_me.sh
source ${HOME}/workspace/ModelDebugger_0.0/source_me.sh

MODEL=FVP_Base_AEMv8A-AEMv8A
MODEL_EXTRA_ARGS=""
MODEL_DEBUG=0
MODELDEBUGGER_OPTS="-y -n"
ATF_TYPE=debug
BL1=${TREE}/arm-trusted-firmware/build/fvp/${ATF_TYPE}/bl1.bin
FIP=${TREE}/arm-trusted-firmware/build/fvp/${ATF_TYPE}/fip.bin

# Load Firmware
MODEL_ARGS="${MODEL_ARGS} -C bp.secureflashloader.fname=${BL1} -C bp.flashloader0.fname=${FIP}"

# Find a free network interface
TAP="";
NUM_TAP_DEVS=`ip link show | grep armtap | wc -l`;
for N in `seq 0 $(($NUM_TAP_DEVS - 1))`; do
        set +e -x
        P=`ip link show dev armtap${N} | grep "NO-CARRIER"`
        set -e -x
        if [ -n "$P" ]; then
                TAP="armtap${N}";
                break;
        fi
done

if [ -z "${TAP}" ]; then
        echo "No Free TAP device found";
        exit 1;
else
	MODEL_ARGS="${MODEL_ARGS} -C bp.hostbridge.interfaceName=${TAP}"

fi

set -x
if [ $MODEL_DEBUG -eq 1 ] ; then
	modeldebugger ${MODEL_PATH}/${MODEL}.so \
		${MODELDEBUGGER_OPTS}\
		-f ${MODEL}.params ${MODEL_ARGS} ${MODEL_EXTRA_ARGS}
else
	model_shell64 --quiet ${MODEL_PATH}/${MODEL}.so \
		-f ${MODEL}.params ${MODEL_ARGS} ${MODEL_EXTRA_ARGS} \
		--run
fi
