LIB = libmsp

# TODO: copy-pasting code from mspware is not nice
OBJECTS = \
	clock.o \
	watchdog.o \
	mspware/pmm.o \
	mem.o \

# pseudo-RNG is only supported with hardware multiplier
ifeq ($(HWMULT),1)
OBJECTS += rand.o
endif

override SRC_ROOT = ../../src

override CFLAGS += \
	-I$(SRC_ROOT)/include/libmsp \
	-I$(SRC_ROOT)/mspware \
