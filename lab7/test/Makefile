obj-m := main.o

KDIR := /lib/modules/`uname -r`/build

all: main.c
	make -C $(KDIR) M=`pwd` modules

clean:
	make -C $(KDIR) M=`pwd` clean

install:
	sudo insmod main.ko

remove:
	sudo rmmod main

test: test.c
	gcc -o test test.c