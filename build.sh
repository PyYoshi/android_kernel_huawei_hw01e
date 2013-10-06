#! /bin/sh

export CCOMPILER=$HOME/android/cyanogenmod/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-
export KERNEL_DIR=$PWD

make ARCH=arm CROSS_COMPILE=$CCOMPILER -j`grep 'processor' /proc/cpuinfo | wc -l`
