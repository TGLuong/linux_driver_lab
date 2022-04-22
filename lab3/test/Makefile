EXTRA_CFLAGS := -Wall
obj-m := charDrv0_Simple.o

KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd`

clean:
	make -C $(KDIR) M=`pwd` clean
