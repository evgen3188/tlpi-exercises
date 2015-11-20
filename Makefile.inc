TLPI_DIR = ./tlpi-dist
TLPI_LIB = $(TLPI_DIR)/libtlpi.a
TLPI_INCL_DIR = $(TLPI_DIR)/lib

OBJ_DIR=obj

CFLAGS = -I../$(TLPI_INCL_DIR) -Wall
LDLIBS = ../$(TLPI_LIB) -lm
