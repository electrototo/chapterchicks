IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = menus.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = menus.o prueba_menu.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prueba_menu: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
