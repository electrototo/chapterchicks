#include <stdio.h>

#include <menus.h>
#include <estructuras.h>

int main(int argc, char **argv) {
    FILE *usuarios_db;
    FILE *libros;

    Usuario usuarios[50];

    usuarios_db = fopen("usuarios.dat", "r");
    if (usuarios_db == NULL) {
    }

    return 0;
}
