IDIR =../include
CC=gcc
LDIR =../lib
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lcrypto

_DEPS = menus.h utilities.h fastpbkdf2.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = menus.o utilities.o fastpbkdf2.o $(name).o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(name): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
