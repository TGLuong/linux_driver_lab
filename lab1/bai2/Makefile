
obj-m := bai2.o

KDIR := /lib/modules/`uname -r`/build

arr ?= 1,2,3,4,5,6,7,8,9,10

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod bai2.ko arr=${arr}
	sudo rmmod bai2
