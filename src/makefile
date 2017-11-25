IDIR =../include
CC=gcc
LDIR =../lib
CFLAGS=-I$(IDIR) -L$(LDIR)

ODIR=obj

LIBS=-lcrypto

_DEPS = menus.h utilities.h estructuras.h fastpbkdf2.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = menus.o utilities.o estructuras.o fastpbkdf2.o $(name).o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(name): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
	rm -f $(ODIR)/*.o
