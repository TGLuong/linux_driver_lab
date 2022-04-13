

MODULE_NAME := bintodec

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

bin ?= 10111010111001

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko bin=${bin}
	sudo rmmod ${MODULE_NAME}
