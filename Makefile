ifeq ($(KERNELRELEASE),)

CROSS		:=	arm-none-linux-gnueabi-

KERNELDIR ?=/home/wxidong/workspace/build/build/kernel/2.6.34/linux-2.6.34-802
CC			=	$(CROSS)gcc
PWD 		:= 	$(shell pwd)
AR			=	$(CROSS)ar
LDSHFLAGS	=	-rdynamic -shared
ARFLAGS		=	rcv


all:modules libat91reg.a libat91reg.so

libat91reg.a:at91reg_api.o
	$(AR) $(ARFLAGS) $@ $^

libat91reg.so:at91reg_api.o
	$(CC) $(LDSHFLAGS) -o $@ $^


modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.order *.symvers  *.a *.so

distclean:
	$(MAKE) clean

.PHONY: modules modules_install clean distclean

else
    obj-m := at91reg.o
endif

