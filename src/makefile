IDIR =../include
CC=gcc
LDIR =../lib
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lcrypto

_DEPS = menus.h utilities.h
_OBJ = menus.o utilities.o $(name).o

ifeq ($(c), elena)
$(warning no vas a poder compilar aleer)
else
_DEPS += fastpbkdf2.h
_OBJ += fastpbkdf2.o
$(info Se incluyo la libreria fastpbkdf2)
endif

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(name): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
