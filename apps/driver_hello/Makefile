#Makefile for driver
# if KERNELRELEASE is defined, we’ve been invoked from the
# kernel build system and can use its language.
ifneq (${KERNELRELEASE},)
	obj-m := hello.o
# Otherwise we were called directly from the command line.
# Invoke the kernel build system.
else
	KERNEL_SOURCE := ${HOME}/lab/linux
	PWD := $(shell pwd)

	# Linux kernel 5.10.131 (one line)
	CC=${HOME}/lab/toolchain/gcc-linaro-12.2.1-2022.09-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
	BUILD=boneblack
	CORES=4
	image=zImage
	PUBLIC_DRIVER_PWD=${HOME}/lab/rootfs/lib/modules/5.10.140/kernel/drivers/hello

default:
	# Trigger kernel build for this module
	${MAKE} -C ${KERNEL_SOURCE} M=${PWD} -j${CORES} ARCH=arm \
		LOCALVERSION=${BUILD} CROSS_COMPILE=${CC} ${address} \
		${image} modules
	# copy result to public folder
	cp *.ko ${PUBLIC_DRIVER_PWD}

clean:
	${MAKE} -C ${KERNEL_SOURCE} M=${PWD} clean
endif
#chmod -R a+rwx