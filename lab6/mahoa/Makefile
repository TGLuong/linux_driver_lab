
obj-m := main.o

KDIR := /lib/modules/`uname -r`/build

k1 ?= 1
k2 ?= qwertyuioplkjhgfdsazxcvbnm
k3 ?= 7,4,10,3,12,2,0,11,6,9,13,5,8,1

all: main.c
	make -C $(KDIR) M=`pwd` modules

install:
	sudo dmesg -C
	sudo insmod main.ko k1=${k1} k2=${k2} k3=${k3}

remove:
	sudo rmmod main

test: test.c
	gcc -o test test.c

clean:
	make -C $(KDIR) M=`pwd` clean