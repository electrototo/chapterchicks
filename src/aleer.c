#include <stdio.h>
#include <string.h>

#include <menus.h>
#include <estructuras.h>
#include <utilities.h>

#include "fastpbkdf2.h"

int main(int argc, char **argv) {
    FILE *usuarios_db;
    FILE *libros;

    ManejoUsuarios usuarios;

    unsigned char password[256], salt[128], hash[256];
    int index;

    char nombre[100], direccion[100], email[100];
    int fecha_nac[3];

    usuarios_db = fopen("usuarios.dat", "r");
    if (usuarios_db == NULL) {
        usuarios_db = fopen("usuarios.dat", "w");
        usuarios.actual = 0;
        fwrite(&usuarios, sizeof(usuarios), 1, usuarios_db);
    }
    else {
        fread(&usuarios, sizeof(usuarios), 1, usuarios_db);
        printf("Se encontraron %d usuarios\n", usuarios.actual);
    }

    fclose(usuarios_db);

    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
        }

        else if (strcmp(argv[1], "-a") == 0) {
            index = usuarios.actual;

            menu_agregar_usuario(
                nombre,
                password,
                fecha_nac,
                direccion,
                email);

            strcpy(usuarios.usuarios[index].nombre, nombre);
            strcpy(usuarios.usuarios[index].contrasena, hash);
            strcpy(usuarios.usuarios[index].direccion, direccion);
            strcpy(usuarios.usuarios[index].email, email);

            usuarios.usuarios[index].activo = 1;
            usuarios.usuarios[index].tipo_usuario = 1;
            usuarios.usuarios[index].disponibles = 3;
            usuarios.usuarios[index].id = index;

            generate_salt(128, salt);
            memcpy(usuarios.usuarios[index].salt, salt, 128);

            fastpbkdf2_hmac_sha256(password, strlen(password), salt,
                128, 4096, hash, 256);

            for (int i = 0; i < 3; i++)
                usuarios.usuarios[index].fecha_nacimiento[i] = fecha_nac[i];

            usuarios.actual++;

            usuarios_db = fopen("usuarios.dat", "w");
            fwrite(&usuarios, sizeof(usuarios), 1, usuarios_db);
            fclose(usuarios_db);
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
