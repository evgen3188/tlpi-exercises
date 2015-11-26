include ../Makefile.inc

WITH_OPT = volatile
WITHOUT_OPT =

_EXE = $(WITH_OPT)-opt $(WITH_OPT) $(WITHOUT_OPT)

EXE = $(patsubst %,$(EXE_DIR)/%,$(_EXE))

all: ${EXE}

.SECONDEXPANSION:
$(EXE_DIR)/$(WITH_OPT)-opt: $$(patsubst $$(EXE_DIR)/%-opt,$$(EXE_DIR)/%,$$@)
	@ echo 'Building opt version'
	$(CC) -O $(CFLAGS) $(LDLIBS) -o $@ $(<F).c

$(EXE_DIR)/%: %.c exe-dir
	@ echo 'Building no-opt version'
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $<

gen-asm: clean-asm $(EXE_DIR)/$(WITH_OPT).s

$(EXE_DIR)/%.s: %.c exe-dir 
	$(CC) -S $(CFLAGS) $<
	mv $(@F) $(EXE_DIR)/$(*F)-noopt.s
	$(CC) -S -O $(CFLAGS) $<
	mv $(@F) $(EXE_DIR)/$(*F)-opt.s

exe-dir:
	@ [ -d $(EXE_DIR) ] || mkdir $(EXE_DIR)

clean:
	${RM} -r $(EXE_DIR)

clean-asm:
	$(RM) $(EXE_DIR)/*.s

showall :
	@ echo $(WITH_OPT) $(WITHOUT_OPT)
