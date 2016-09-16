LIB = libmsp

# We need the device information for later in this makefile.
# Note that normally this is included automatically by Makefile.gcc
include $(MAKER_ROOT)/Makefile.board

# TODO: copy-pasting code from mspware is not nice
OBJECTS = \
	watchdog.o \
	mspware/pmm.o \
	mem.o \

# TODO: clock setup is not supported for this device
ifneq ($(DEVICE),msp430fr5949)
	OBJECTS += clock.o
endif # DEVICE

# pseudo-RNG is only supported with hardware multiplier
ifeq ($(HWMULT),1)
OBJECTS += rand.o
endif

override SRC_ROOT = ../../src

override CFLAGS += \
	-I$(SRC_ROOT)/include/libmsp \
	-I$(SRC_ROOT)/mspware \

include ../Makefile.config
