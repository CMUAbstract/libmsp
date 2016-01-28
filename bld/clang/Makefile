EXEC = libmsp.a.bc

OBJECTS = \
	clock.o \
	watchdog.o \
	mspware/pmm.o \
	mem.o \

SRC_DIR = ../../src

CFLAGS += \
	-I$(SRC_DIR)/include/libmsp \
	-I$(SRC_DIR)/mspware \

include $(MAKER_ROOT)/Makefile.clang
