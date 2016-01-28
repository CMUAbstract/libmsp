LIB = libmsp
EXEC = $(LIB).a

# TODO: copy-pasting code from mspware is not nice
OBJECTS = \
	clock.o \
	watchdog.o \
	mspware/pmm.o \

override SRC_ROOT = ../../src

CFLAGS += \
	-I$(SRC_ROOT)/include/$(LIB) \
	-I$(SRC_ROOT)/mspware \

include $(MAKER_ROOT)/Makefile.gcc
