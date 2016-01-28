EXEC = libmsp.a.bc

OBJECTS = \
	clock.o \
	watchdog.o \
	mspware/pmm.o \
	mem.o \

include $(MAKER_ROOT)/Makefile.clang

SRC_DIR = ../../src

CFLAGS += \
	-I$(SRC_DIR)/include/libmsp \
	-I$(SRC_DIR)/mspware \
