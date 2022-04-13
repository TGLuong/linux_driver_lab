

MODULE_NAME := hextooct

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

hex ?= 2eb9

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko hex=${hex}
	sudo rmmod ${MODULE_NAME}
