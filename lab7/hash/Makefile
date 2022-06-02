obj-m := main.o

KDIR := /lib/modules/`uname -r`/build

all: main.c
	make -C $(KDIR) M=`pwd` modules

clean:
	make -C $(KDIR) M=`pwd` clean