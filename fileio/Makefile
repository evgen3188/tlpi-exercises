include ../Makefile.inc

_EXE = tee

EXE = $(patsubst %,$(EXE_DIR)/%,$(_EXE))

all: ${EXE}

$(EXE_DIR)/%: %.c
	@ [ -d $(EXE_DIR) ] || mkdir $(EXE_DIR)
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

clean:
	${RM} -r $(EXE_DIR)

showall :
	@ echo $(_EXE)
