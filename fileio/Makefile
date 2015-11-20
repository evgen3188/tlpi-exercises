include ../Makefile.inc

_OBJS = tee

OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

all: ${OBJS}

$(OBJ_DIR)/%: %.c
	@ [ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

clean:
	${RM} -rf $(OBJ_DIR)

showall :
	@ echo ${OBJS}
