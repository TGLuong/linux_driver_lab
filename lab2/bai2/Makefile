

MODULE_NAME := bai2

obj-m := ${MODULE_NAME}.o

KDIR := /lib/modules/`uname -r`/build

string ?= tran gia luong
endc ?= 0
s1 ?= tran
s2 ?= luong

all:
	make -C ${KDIR} M=`pwd`

clean:
	make -C ${KDIR} M=`pwd` clean

install:
	sudo dmesg -C
	sudo insmod ${MODULE_NAME}.ko string='"${string}"' endc=${endc} s1='"${s1}"' s2='"${s2}"'
	sudo rmmod ${MODULE_NAME}
