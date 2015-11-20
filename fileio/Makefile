include ../Makefile.inc

_OBJS = tee

OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

all: ${OBJS}

$(OBJ_DIR)/%: %.c
	@ [ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	${RM} -rf $(OBJ_DIR)

showall :
	@ echo ${OBJS}
