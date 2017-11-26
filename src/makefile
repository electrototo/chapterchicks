IDIR =../include
CC=gcc
LDIR =../lib
CFLAGS=-I$(IDIR) -L$(LDIR)

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

ifeq ($(c), antares)
$(info debes tener myapps en tu directorioo HOME con openssl instalado)
CFLAGS += -I$(HOME)/myapps/include -L$(HOME)/myapps/lib
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
