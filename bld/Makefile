LIB = libmsp

# We need the device information for later in this makefile.
# Note that normally this is included automatically by Makefile.gcc
include $(MAKER_ROOT)/Makefile.board

# TODO: copy-pasting code from mspware is not nice
OBJECTS += \
	watchdog.o \
	mspware/pmm.o \
	mem.o \
	clock.o \

ifneq ($(LIBMSP_SLEEP_TIMER),)
OBJECTS += sleep.o
endif # LIBMSP_SLEEP_TIMER

ifneq ($(LIBMSP_UART_IDX),)
OBJECTS += uart.o
endif # LIBMSP_UART_IDX

ifneq ($(LIBMSP_TICK_TIMER),)
OBJECTS += tick.o
endif # LIBMSP_TICK

ifneq ($(LIBMSP_TEMP),)
OBJECTS += temp.o
endif # LIBMSP_TEMP

# pseudo-RNG is only supported with hardware multiplier
ifeq ($(HWMULT),1)
OBJECTS += rand.o
endif

#DEPS += libio \

override SRC_ROOT = ../../src

override CFLAGS += \
	-I$(SRC_ROOT)/ \
	-I$(SRC_ROOT)/include/ \
	-I$(SRC_ROOT)/include/$(LIB) \
	-I$(SRC_ROOT)/mspware \



