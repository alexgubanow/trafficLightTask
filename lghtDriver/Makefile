obj-m := lghtIO.o
KernHead := /lib/modules/$(shell uname -r)/build
ProjDir := $(shell pwd)

all: module

module:
	$(MAKE) -C $(KernHead) SUBDIRS=$(ProjDir) modules

clean:
	$(MAKE) -C $(KernHead) SUBDIRS=$(ProjDir) clean