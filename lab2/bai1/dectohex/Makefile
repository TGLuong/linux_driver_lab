

MODULE_NAME := dectohex

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

dec=349

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko dec=${dec}
	sudo rmmod ${MODULE_NAME}
