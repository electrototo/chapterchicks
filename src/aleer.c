#include <stdio.h>
#include <string.h>

#include <menus.h>
#include <estructuras.h>
#include <utilities.h>

#include "fastpbkdf2.h"

int main(int argc, char **argv) {
    // archivos en los que se almacenan las bases de datos
    FILE *usuarios_db;
    FILE *biblioteca_db;
    FILE *autores_db;
    FILE *categorias_db;
    FILE *users_export;

    ManejoUsuarios usuarios;
    ManejoAutor autores;
    ManejoCategoria categorias;

    Usuario *usuario;

    Biblioteca biblioteca;

    // variables para la creacion de un usuario
    unsigned char password[256], salt[128], hash[256];
    unsigned char msg[200];

    float credito = 0;
    unsigned char a_credito[10];

    int index;

    // variables para el registro del usuario
    char nombre[100], direccion[100], email[100];
    int fecha_nac[3];

    // variables para el registro de un libro
    char nombre_libro[100], nombre_autor[50], categoria[50], isbn[14];
    float precio;

    // variables que lleva el flujo de las elecciones del usuario
    int success = 0, login_index = 0, found = 0;

    int eleccion, export;

    int lookup_id;

    // aqui se pueden crear funciones

    // carga de la base de datos de usuarios en la memoria
    // (puede ser eficientizado)
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
        printf("Se encontraron %d usuarios\n", usuarios.actual);
    }
    fclose(usuarios_db);

    // carga de la base de datos de libros en la memoria
    // (puede ser eficientizado)
    biblioteca_db = fopen("biblioteca.dat", "r");
    if (biblioteca_db == NULL) {
        biblioteca_db = fopen("biblioteca.dat", "w");
        biblioteca.actual = 0;

        sprintf(msg, "Creacion de base de datos para libros");
        log_msg(msg);

        fwrite(&biblioteca, sizeof(biblioteca), 1, biblioteca_db);
    }
    else {
        fread(&biblioteca, sizeof(biblioteca), 1, biblioteca_db);
        printf("Se encontraron %d libros\n", biblioteca.actual);
    }
    fclose(biblioteca_db);

    // carga de la base de datos de autores en la memoria
    autores_db = fopen("autores.dat", "r");
    if(autores_db == NULL) {
        autores_db = fopen("autores.dat", "w");
        autores.actual = 0;

        sprintf(msg, "Creacion de base de datos para autores");
        log_msg(msg);

        fwrite(&autores, sizeof(autores), 1, autores_db);
    }
    else {
        fread(&autores, sizeof(autores), 1, autores_db);
        printf("Se encontraron %d autores\n", autores.actual);
    }
    fclose(autores_db);

    // carga de la base de datos de categorias
    categorias_db = fopen("categorias.dat", "r");
    if(categorias_db == NULL) {
        categorias_db = fopen("categorias.dat", "w");
        categorias.actual = 0;

        sprintf(msg, "Creacion de base de datos para categorias");
        log_msg(msg);

        fwrite(&categorias, sizeof(categorias), 1, categorias_db);
    }
    else {
        fread(&categorias, sizeof(categorias), 1, categorias_db);
        printf("Se encontraron %d categorias\n\n", categorias.actual);
    }
    fclose(categorias_db);


    // si al momento de ejecutar el codigo hubieron argumentos
    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
        }

        else if (strcmp(argv[1], "-a") == 0)
            add_user(&usuarios, ADMIN);

        else if (strcmp(argv[1], "-usu") == 0) {
            if (argc == 3)
                if (strcmp(argv[2], "csv") == 0)
                    export = 1;

            if (export) {
                users_export = fopen("usuarios.csv", "w");
                fprintf(users_export, "Nombre del usuario,Correo electronico,Activo\n");
            }

            for (int i=0; i < usuarios.actual; i++){
                if (export)
                    fprintf(users_export, "%s,%s,%d\n", usuarios.usuarios[i].nombre, usuarios.usuarios[i].email, usuarios.usuarios[i].activo);

                printf("Usuario: %s\n", usuarios.usuarios[i].nombre);
                printf("Email: %s\n", usuarios.usuarios[i].email);

                if (usuarios.usuarios[i].activo)
                    printf("El usuario se encuentra activo\n");
                else
                    printf("El usuario se encuentra desactivo\n");

                printf("\n");
            }

            if (export)
                fclose(users_export);
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

    // esto serivira a futura para no tener que escribir
    // usuarios.usuarios[login_index] cada vez que se quiera
    // acceder a la informacion del usuario actual
    usuario = &usuarios.usuarios[login_index];

    // hay que comprobar si no hubo tampering con el credito de la
    // persona
    sprintf(a_credito, "%f", usuario->credito);
    fastpbkdf2_hmac_sha256(a_credito, strlen(a_credito), usuario->c_salt,
        128, 4096, hash, 256);

    if (memcmp(hash, usuario->c_hash, 256) != 0) {
        // hubo tampering de data
        usuario->activo = 0;

        sprintf(msg, "Tampering de data encontrado con el usuario %s", usuario->email);
        log_msg(msg);

        usuarios_db = fopen("usuarios.dat", "w");
        fwrite(&usuarios, sizeof(usuarios), 1, usuarios_db);
        fclose(usuarios_db);
    }

    // como usuario es un apuntador a una estructura, sus atributos
    // ya no se acceden con puntitos, sino que con flechas
    if (!usuario->activo) {
        printf("\nLo lamentamos, tu cuenta fue desactivada\n\n");

        return 1;
    }

    eleccion = 0; 
    if (usuario->tipo_usuario == ADMIN)
        eleccion = menu_administrador_como();

    //    int eleccion2;
    
    // el administrador decidió entrar como administrador
    if (eleccion == 1) {
        while ((eleccion = menu_administrador_general()) != 7) {
            printf("eleccion: %d\n", eleccion);

            switch (eleccion) {
                case 1:
                    //informe de libros en préstamo
                    //no estoy imprimiendo los prestamos
                    break;

                case 2:
                //Informe de usuarios dados de alta y libros en préstamo
                break;

                case 3:
                    menu_registrar_libro(
                        biblioteca.libros[biblioteca.actual].titulo, 
                        nombre_autor,
                        categoria,
                        biblioteca.libros[biblioteca.actual].ISBN10, 
                        biblioteca.libros[biblioteca.actual].ISBN13, 
                        &biblioteca.libros[biblioteca.actual].costo, 
                        &biblioteca.libros[biblioteca.actual].a_pub,
                        biblioteca.libros[biblioteca.actual].editorial
                    );

                    // busca si existe el autor especificado para el libro
                    // asumimos que el autor existe para el libro
                    success = 0;
                    for (int i = 0; i < autores.actual; i++) {
                        if (strcmp(autores.autores[i].nombre, nombre_autor) == 0) {
                            lookup_id = autores.autores[i].id;
                            success = 1;
                            // ya no es necesario seguir buscando
                            break;
                        }
                    }
                    
                    // no se encontro el autor, por lo tanto se deberia crear
                    if (!success) {
                        strcpy(autores.autores[autores.actual].nombre, nombre_autor);
                        autores.autores[autores.actual].id = autores.actual;

                        autores.actual++;

                        sprintf(msg, "Creacion del autor %s", nombre_autor);
                        log_msg(msg);

                        // guarda el autor, porque actualmente no existe en la
                        // base de datos
                        autores_db = fopen("autores.dat", "w");
                        fwrite(&autores, sizeof(autores), 1, autores_db);
                        fclose(autores_db);
                    }

                    biblioteca.libros[biblioteca.actual].autor = lookup_id;

                    // busca si existe el genero especificado para el libro
                    // elena, completa la funcion

                    // busca si existe la categoria específica
                    success = 0;
                    for (int i = 0; i < categorias.actual; i++) {
                        if (strcmp(categorias.categorias[i].nombre, categoria) == 0) {
                            lookup_id = categorias.categorias[i].id;
                            success = 1;
                            // ya no es necesario seguir buscando
                            break;
                        }
                    }

                    // no se encontro la categoria, por lo tanto se deberia crear
                    if (!success) {
                        strcpy(categorias.categorias[categorias.actual].nombre, categoria);
                        categorias.categorias[categorias.actual].id = categorias.actual;

                        categorias.actual++;

                        sprintf(msg, "Creacion del la categoría %s", categoria);
                        log_msg(msg);

                        // guarda la categoria, porque actualmente no existe en la
                        // base de datos
                        categorias_db = fopen("categorias.dat", "w");
                        fwrite(&categorias, sizeof(categorias), 1, categorias_db);
                        fclose(categorias_db);
                    }

                    biblioteca.libros[biblioteca.actual].categoria = lookup_id;
            
                    biblioteca.actual++;

                    // guarda los cambios que se crearon en la biblioteca
                    biblioteca_db = fopen("biblioteca.dat", "w");
                    fwrite(&biblioteca, sizeof(biblioteca), 1, biblioteca_db);
                    fclose(biblioteca_db);

                    break;

                case 4:
                    //baja de un cliente
                    menu_baja_de_usuario(email);

                    // busca el usuario para darlo de baja
                    found = 0;
                    for (int i = 0; i < usuarios.actual; i++) {
                        if (strcmp(usuarios.usuarios[i].email, email) == 0) {
                            found = 1;

                            sprintf(msg, "Se dio de baja el usuario %s por el administrador %s", email, usuario->nombre);
                            log_msg(msg);

                            // pone la bandera de activo en falso
                            usuarios.usuarios[i].activo = 0;

                            // guarda los usuarios
                            usuarios_db = fopen("usuarios.dat", "w");
                            fwrite(&usuarios, sizeof(usuarios), 1, usuarios_db);
                            fclose(usuarios_db);

                            break;
                        }
                    }

                    if (!found)
                        printf("\tEl usuario especificado no existe\n");
                    else
                        printf("\tEl usuario fue exitosamente dado de baja\n");

                    break;

                case 5:
                    menu_popular();
                    break;

                case 6:
                    menu_ayuda();
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
    else if (eleccion == 2 || usuario->tipo_usuario == MORTAL) {
        while((eleccion = menu_usuario()) != 4){
            switch(eleccion) {
                case 1:
                    // accesar al catalogo de libros
                    // aqui se podria mejorar mostrando un menu que pregunte por
                    // la categoria en vez de mostrar todos los libros
                    for (int i = 0; i < biblioteca.actual; i++) {
                        printf("Título: %s\n", biblioteca.libros[i].titulo);
                        printf("\tAutor: %c\n", *autores.autores[i].nombre);
                        printf("\tCategoría: %c\n", *categorias.categorias[i].nombre);
                        printf("\tISBN 10: %s\n", biblioteca.libros[i].ISBN10);
                        printf("\tISBN 13: %s\n", biblioteca.libros[i].ISBN13);
                        printf("\tCosto: %.2f\n", biblioteca.libros[i].costo);
                        printf("\tAño de publicación: %d\n", biblioteca.libros[i].a_pub);
                        printf("\tEditorial: %s\n\n", biblioteca.libros[i].editorial);
                    }
                    break;

                case 2:
                    // mostrar los libros en prestamo
                    break;

                case 3:
                    // devolver un libro
                    break;

                default:
                    break;
            }
        }
    }

    return 0;
}
