# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
obj-m := CharDriver_k.o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	cc CharDriverTest.c -o CharDriverTest
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm CharDriverTest
endif