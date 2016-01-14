LIB = libmsp
EXEC = $(LIB).a

# TODO: copy-pasting code from mspware is not nice
OBJECTS = \
	clock.o \
	mspware/pmm.o \

include $(MAKER_ROOT)/Makefile.gcc

SRC_DIR = ../../src

CFLAGS += \
	-I$(SRC_DIR)/include/$(LIB) \
	-I$(SRC_DIR)/mspware \

VPATH = $(SRC_DIR)
