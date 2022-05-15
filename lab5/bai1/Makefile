
obj-m := bai1.o
KDIR := /lib/modules/`uname -r`/build


all:
	make -C $(KDIR) M=`pwd` modules

test: test.c
	gcc -o test test.c

clean:
	make -C $(KDIR) M=`pwd` clean
