IDIR =../include
CC=gcc
LDIR =../lib
CFLAGS=-I$(IDIR) -L$(LDIR)

ODIR=obj

LIBS=-lcrypto -lfastpbkdf2

_DEPS = menus.h utilities.h estructuras.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = menus.o utilities.o estructuras.o $(name).o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(name): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
