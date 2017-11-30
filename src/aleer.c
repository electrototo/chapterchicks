#include <stdio.h>
#include <string.h>

#include <menus.h>
#include <estructuras.h>
#include <utilities.h>

#include "fastpbkdf2.h"

#define ADMIN 1
#define MORTAL 0

int main(int argc, char **argv) {
    FILE *usuarios_db;
    FILE *libros;
    FILE *users_export;

    ManejoUsuarios usuarios;
    Usuario usuario;

    unsigned char password[256], salt[128], hash[256];
    unsigned char msg[200];

    float credito = 0;
    unsigned char a_credito[10];

    int index;

    char nombre[100], direccion[100], email[100];
    int fecha_nac[3];

    int success = 0, login_index = 0, found = 0;

    int eleccion;

    usuarios_db = fopen("usuarios.dat", "r");
    if (usuarios_db == NULL) {
        usuarios_db = fopen("usuarios.dat", "w");
        usuarios.actual = 0;

        sprintf(msg, "Creacion de base de datos para usuarios");
        log_msg(msg);

        fwrite(&usuarios, sizeof(usuarios), 1, usuarios_db);
    }
    else {
        fread(&usuarios, sizeof(usuarios), 1, usuarios_db);
        printf("Se encontraron %d usuarios\n\n", usuarios.actual);
    }

    fclose(usuarios_db);

    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
        }

        else if (strcmp(argv[1], "-a") == 0) {
            add_user(&usuarios, ADMIN);
        }

        else if (strcmp(argv[1], "-usu") == 0) {
            if (argc == 3) {
                if (strcmp(argv[2], "csv") == 0) {
                    users_export = fopen("usuarios.csv", "w");

                    fprintf(users_export, "Nombre del usuario,Correo electronico,Activo\n");

                    for (int i=0; i < usuarios.actual; i++)
                        fprintf(users_export, "%s,%s,%d\n", usuarios.usuarios[i].nombre, usuarios.usuarios[i].email, usuarios.usuarios[i].activo);

                    fclose(users_export);
                }
            }

            for (int i=0; i < usuarios.actual; i++){
                printf("Usuario: %s\n", usuarios.usuarios[i].nombre);
                printf("Email: %s\n", usuarios.usuarios[i].email);

                if (usuarios.usuarios[i].activo)
                    printf("El usuario se encuentra activo\n");
                else
                    printf("El usuario se encuentra desactivo\n");

                printf("\n");
            }
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

    creditos();

    eleccion = menu_principal();

    if (eleccion == 1) {
        success = 0;
        while (!success) {
            menu_acceso(email, password);

            for (int i = 0; i < usuarios.actual; i++) {
                if(strcmp(usuarios.usuarios[i].email, email) == 0) {
                    found = 1;

                    fastpbkdf2_hmac_sha256(password, strlen(password),
                        usuarios.usuarios[i].salt, 128, 4096, hash, 256);

                    if (memcmp(usuarios.usuarios[i].contrasena, hash, 256) == 0) {
                        success = 1;
                        login_index = i;

                        sprintf(msg, "Login exitoso para %s", email);
                        log_msg(msg);

                    }
                    else {
                        sprintf(msg, "Contrasena incorrecta para %s", email);
                        log_msg(msg);

                        printf("\tLa contraseña es incorrecta\n");
                    }

                    break;
                }
            }

            if (!found)
                printf("\n\tEl usuario especificado no existe\n\n");
        }
    }
    else
        login_index = add_user(&usuarios, MORTAL);

    if (!usuarios.usuarios[login_index].activo) {
        printf("\nLo lamentamos, tu cuenta fue desactivada\n\n");

        return 1;
    }

    eleccion = 0; 
    if (usuarios.usuarios[login_index].tipo_usuario == ADMIN)
        eleccion = menu_administrador_como();

    // el administrador decidio entrar como administrador
    if (eleccion == 1) {
        while ((eleccion = menu_administrador_general()) != 7) {
            switch (eleccion) {
                case 1:
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                case 6:
                    break;

                case 7:
                    break;

                default:
                    break;
            }
        }
    }
    // el administrador decidio como usuario o la cuenta es de tipo
    // usuario
    else if (eleccion == 2 || usuarios.usuarios[login_index].tipo_usuario == MORTAL) {
        while((eleccion = menu_usuario()) != 4){
            switch(eleccion) {
                case 1:
                    break;

                case 2:
                    break;

                case 3:
                    break;

                default:
                    break;
            }
        }
    }

    return 0;
}
