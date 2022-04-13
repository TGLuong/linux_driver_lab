obj-m := bai1.o
MODULE_FILE := bai1.ko

choice ?= 1
arr ?= 0,1,2,3,4,5,6,7,8,9,10
a ?= 12
b ?= 9

KDIR := /lib/modules/`uname -r`/build

all:
	make -C ${KDIR} M=`pwd` 

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_FILE} choice=${choice} arr=${arr} a=${a} b=${b}
	sudo rmmod ${MODULE_FILE}

echo:
	echo ${choice}
	echo ${arr}
