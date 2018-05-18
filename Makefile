LIB = libmsp

# We need the device information for later in this makefile.
# Note that normally this is included automatically by Makefile.gcc
include $(MAKER_ROOT)/Makefile.board

# TODO: copy-pasting code from mspware is not nice
OBJECTS = \
	watchdog.o \
	mem.o \
	clock.o \

ifneq ($(LIBMSP_SLEEP_TIMER),)
ifneq ($(TOOLCHAIN),clang)
OBJECTS += sleep.o
else # TOOLCHAIN == clang
$(error libmsp/sleep.c currently not supported with Clang)
# because: __bic_SR_register_on_exit() not implemented in LLVM.
# See here for ideas on how to do it:
# https://github.com/rust-lang-nursery/embedded-wg/issues/20#issuecomment-296538976
endif # TOOLCHAIN == clang
endif # LIBMSP_SLEEP_TIMER

ifneq ($(LIBMSP_UART_IDX),)
ifneq ($(TOOLCHAIN),clang)
OBJECTS += uart.o
else # TOOLCHAIN == clang
$(error libmsp/uart.c currently not supported with Clang)
# because: (see sleep.c case above)
endif # TOOLCHAIN == clang
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

override SRC_ROOT = ../../src

override CFLAGS += \
	-I$(SRC_ROOT)/include/libmsp \

include $(MAKER_ROOT)/Makefile.$(TOOLCHAIN)
