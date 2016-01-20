TLPI_DIR = tlpi-dist
TLPI_LIB = $(TLPI_DIR)/libtlpi.a
TLPI_INCL_DIR = $(TLPI_DIR)/lib
EXCEPT_DIRS = $(TLPI_DIR)

EXE_DIR=exe

CFLAGS = -I../$(TLPI_INCL_DIR) -Wall
LDLIBS = ../$(TLPI_LIB) -lm

BASE_MAKE = base.mk
