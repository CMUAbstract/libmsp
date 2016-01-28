EXEC = libmsp.a.bc

OBJECTS = \
	clock.o \
	watchdog.o \
	mspware/pmm.o \
	mem.o \

override SRC_ROOT = ../../src

CFLAGS += \
	-I$(SRC_ROOT)/include/libmsp \
	-I$(SRC_ROOT)/mspware \

include $(MAKER_ROOT)/Makefile.clang
