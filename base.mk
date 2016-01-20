include ../Makefile.inc

#EXE = $(patsubst %,$(EXE_DIR)/%,$(_EXE))
C_FILES := $(shell ls *c)
EXE := $(shell basename -s .c -a $(C_FILES) | tr '\n' ' ')

all: prebuilt $(EXE)

prebuilt:
	@ [ -d $(EXE_DIR) ] || mkdir $(EXE_DIR)

$(EXE):
	@echo $@
	$(CC) $(CFLAGS) $@.c $(LDLIBS) -o $(EXE_DIR)/$@

clean:
	${RM} -r $(EXE_DIR)

showall :
	@echo $(EXE)
