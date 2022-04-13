

MODULE_NAME := octtohex

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

oct ?= 27271

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko oct=${oct}
	sudo rmmod ${MODULE_NAME}
