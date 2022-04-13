

MODULE_NAME := bai4

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

matrix ?= 6,9,12,15,18

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko arr=${matrix}
	sudo rmmod ${MODULE_NAME}
