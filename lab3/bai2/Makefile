

MODULE_NAME := bai2

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

plant_text ?= '"tran gia luong"'

k1 ?= 1
k2 ?= qwertyuioplkjhgfdsazxcvbnm
k3 ?= 7,4,10,3,12,2,0,11,6,9,13,5,8,1


all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko plant_text=${plant_text} k1=${k1} k2=${k2} k3=${k3}
	sudo rmmod ${MODULE_NAME}
