
obj-m := char-dv-0.o
KDIR := /lib/modules/`uname -r`/build


all:
	make -C $(KDIR) M=`pwd` modules

clean:
	make -C $(KFIR) M=`pwd` clean
