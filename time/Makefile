obj-m := main.o
KDIR := /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd` modules

clean:
	make -C $(KDIR) M=`pwd` clean

load:
	sudo dmesg -C
	sudo insmod main.ko
	sudo rmmod main
	dmesg
