

MODULE_NAME := bintooct

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

bin ?= 101011101

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko bin=${bin}
	sudo rmmod ${MODULE_NAME}
