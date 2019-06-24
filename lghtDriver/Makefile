#output object
obj-m := lghtIO.o
#path to kernel headers on this machine
KernHead := /lib/modules/$(shell uname -r)/build
#path to project directory
ProjDir := $(shell pwd)
#rule to compile all
all: module
#rule to compile module
module:
	$(MAKE) -C $(KernHead) SUBDIRS=$(ProjDir) modules
#rule to do cleaning, to remove produced objects
clean:
	$(MAKE) -C $(KernHead) SUBDIRS=$(ProjDir) clean