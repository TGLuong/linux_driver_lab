

MODULE_NAME := bai1

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

vector1 ?= 1,2,3,4,5,6,7
vector2 ?= 4,5,6,7,8,9,10

width_1 ?= 3
height_1 ?= 3
matrix1 ?= 1,2,3,4,5,6,7,8,9

width_2 ?= 3
height_2 ?= 3
matrix2 ?= 9,8,7,6,5,4,3,2,1

n ?= 10
k ?= 5

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko vector1=${vector1} vector2=${vector2} \
		width_1=${width_1} height_1=${height_1} matrix1=${matrix1} \
		width_2=${width_2} height_2=${height_2} matrix2=${matrix2} \
		n=${n} k=${k}
	sudo rmmod ${MODULE_NAME}
