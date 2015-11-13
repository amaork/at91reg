ifeq ($(KERNELRELEASE),)


CROSS		:=	arm-none-linux-gnueabi-

KERNELDIR ?=/home/wxidong/workspace/build/build/kernel/2.6.34/linux-2.6.34-802
CC			=	$(CROSS)gcc
PWD 		:= 	$(shell pwd)
AR			=	$(CROSS)ar
CPPFLAGS	=	-Wall
LDSHFLAGS	=	-rdynamic -shared  
ARFLAGS		=	rcv


all:libat91reg.a libat91reg.so

libat91reg.a:
	$(AR) $(ARFLAGS) $@ $^

libat91reg.so:
	$(CC) $(LDSHFLAGS) -o $@ $^

depend:$(wildcard *.c)
	$(CC) $(LDFLAGS) -MM $^ > $@

libat91reg.a: 	init.o gpio.o pmc.o
libat91reg.so:	init.o gpio.o pmc.o 


modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.order *.symvers  *.a *.so depend

distclean:
	$(MAKE) clean

-include depend

.PHONY: modules modules_install clean distclean

else
    obj-m := at91reg.o
endif

