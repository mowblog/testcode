obj-m:=test.o  
testmodule-objs:=module  
#KDIR:=/lib/modules/2.6.32-279.el6.i686/build
#KDIR:=/root/kernel/linux-3.12.6
#KDIR:=/usr/src/kernels/2.6.32-279.el6.i686/
KDIR:=/usr/src/linux-headers-4.10.0-28-generic/
MAKE:=make  
default:  
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules  
clean:  
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean  
