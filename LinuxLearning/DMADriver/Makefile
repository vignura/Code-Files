# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
obj-m += DMA_Driver.o 
DMA_Driver-objs+= Driver_k.o DMA_Fun.o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	cc DMADriverTest.c -o DMADriverTest
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm DMADriverTest
endif