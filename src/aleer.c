#include <stdio.h>
#include <string.h>

#include <menus.h>
#include <estructuras.h>

int main(int argc, char **argv) {
    FILE *usuarios_db;
    FILE *libros;

    ManejoUsuarios usuarios;

    int index;
    char password[32];

    usuarios_db = fopen("usuarios.dat", "r");
    if (usuarios_db == NULL) {
        usuarios_db = fopen("usuarios.dat", "w");
        usuarios.actual = 0;
        fwrite(&usuarios, sizeof(usuarios), 1, usuarios_db);
    }
    else
        fread(&usuarios, sizeof(usuarios), 1, usuarios_db);

    fclose(usuarios_db);

    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
        }

        else if (strcmp(argv[1], "-a") == 0) {
            index = usuarios.actual;
            menu_agregar_usuario(
                usuarios.usuarios[index].nombre,
                password,
                usuarios.usuarios[index].fecha_nacimiento,
                usuarios.usuarios[index].direccion);
        }

        else if (strcmp(argv[1], "-usu") == 0) {
        }

        else {
            printf("Uso aleer:\n");
            printf("\t-h\t\tDespliega este menú de ayuda\n");
            printf("\t-a\t\tIndica al programa que se quiere crear una cuenta de administrador\n");
            printf("\t-c\t\tDespliega un informe de libros en préstamo\n");
            printf("\t-usu\t\tDespliega el listado de todos los usuarios del servicio catalogados y muestra su alta y baja\n");
        }

        return 0;
    }

    return 0;
}
