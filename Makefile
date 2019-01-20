#ifneq (${KERNELRELEADE},)
obj-m :=list_head.o

#else

KDIR = /lib/modules/${shell uname -r}/build

all:
	make -C ${KDIR} M=${shell pwd} modules

clean:
	make -C ${KDIR} M=${shell pwd} clean

#endif