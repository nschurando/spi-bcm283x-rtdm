INSTALL_DIR ?= ../release
PWD ?= $(shell pwd)
GIT_VERSION = $(shell cd $(PWD) && git describe --always --dirty --long)

obj-m += spi-bcm283x-rtdm.o 
spi-bcm283x-rtdm-y := ../ksrc/bcm2835.o ../ksrc/spi-bcm283x-rtdm.o
ccflags-y += -I$(KERNEL_DIR)/include/xenomai
ccflags-y += -DGIT_VERSION=\"$(GIT_VERSION)\"

.PHONY: all build clean install

all: build info install

build:
	make -C $(KERNEL_DIR) M=$(PWD) modules

info:
	modinfo spi-bcm283x-rtdm.ko

install:
	@mkdir -p $(INSTALL_DIR)
	cp spi-bcm283x-rtdm.ko $(INSTALL_DIR)/spi-bcm283x-rtdm.ko

clean:
	@make -C $(KERNEL_DIR) M=$(PWD) clean
	@rm -f ../ksrc/*.o
	@rm -f ../ksrc/.*.o.*
