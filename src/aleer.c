#include <stdio.h>
#include <string.h>
#include <time.h>

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
    FILE *prestamos_db;
    FILE *users_export;

    ManejoUsuarios usuarios, usuarios_cpy;
    ManejoAutor autores;
    ManejoCategoria categorias;
    ManejoPrestamo prestamos;

    Usuario *usuario;

    Biblioteca biblioteca;

    Libro libro;
    Categoria categoria_popular;
    Autor autor_popular;
    Prestamo *prestamo;

    // variables para la creación de un usuario
    unsigned char password[256], salt[128], hash[256];
    unsigned char msg[200];

    float credito = 0;
    unsigned char a_credito[10];

    int index, tmp;

    // variables para el registro del usuario
    char nombre[100], direccion[100], email[100];
    int fecha_nac[3];

    // variables para el registro de un libro
    char nombre_libro[100], nombre_autor[50], categoria[50], isbn[14];
    float precio;

    // variables que lleva el flujo de las elecciones del usuario
    int success = 0, login_index = 0, found = 0;

    int eleccion, eleccion2, eleccion_principal, export, opcion_alta_o_baja;

    int lookup_id, max = 0, cat_count = 0;

    time_t diferencia;

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

    //carga de la base de datos de los prestamos
    prestamos_db = fopen("prestamos.dat", "r");
    if(prestamos_db == NULL) {
        prestamos_db = fopen("prestamos.dat", "w");
        prestamos.actual = 0;

        sprintf(msg, "Creacion de base de datos para prestamos");
        log_msg(msg);

        fwrite(&prestamos, sizeof(prestamos), 1, prestamos_db);
    }
    else {
        fread(&prestamos, sizeof(prestamos), 1, prestamos_db);
        printf("Se encontraron %d prestamos\n\n", prestamos.actual);
    }
    fclose(prestamos_db);


    // si al momento de ejecutar el código hubieron argumentos
    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
        }

        else if (strcmp(argv[1], "-a") == 0) {
            if(add_user(&usuarios, ADMIN) == -1)
                printf("\t Debes ser mayor de edad para poder hacer uso del sistema\n");
        }

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
    else {
        login_index = add_user(&usuarios, MORTAL);

        if (login_index == -1) {
            printf("\t Debes ser mayor de edad para poder hacer uso del sistema\n");

            return 1;
        }
    }

    // esto serivirá a futuro para no tener que escribir
    // usuarios.usuarios[login_index] cada vez que se quiera
    // acceder a la información del usuario actual
    usuario = &usuarios.usuarios[login_index];

    // hay que comprobar si no hubo tampering con el crédito de la
    // persona
    sprintf(a_credito, "%f", usuario->credito);
    fastpbkdf2_hmac_sha256(a_credito, strlen(a_credito), usuario->c_salt,
        128, 4096, hash, 256);

    if (memcmp(hash, usuario->c_hash, 256) != 0) {
        // hubo tampering de data
        usuario->activo = 0;

        sprintf(msg, "Tampering de data encontrado con el usuario %s", usuario->email);
        log_msg(msg);

        save_db(&usuarios, sizeof(usuarios), "usuarios.dat");
    }

    // como usuario es un apuntador a una estructura, sus atributos
    // ya no se acceden con puntitos, sino que con flechas
    if (!usuario->activo) {
        printf("\nLo lamentamos, tu cuenta fue desactivada\n\n");

        return 1;
    }

    // comprueba que no haya ningun libro caduco dentro de los libros del usuario
    for (int id = 0; id < 3 - usuario->disponibles; id++) {
        // Busca la ficha de prestamo
        for (int i = 0; i < prestamos.actual; i++) {
            prestamo = &prestamos.prestamos[i];

            if (prestamo->libro == usuario->libros[id] && prestamo->usuario == usuario->id) {
                if (difftime(prestamo->fecha_devolucion, time(NULL)) < 0) {
                    // mueve de lugar los libros prestados
                    for (int j = id; j < 2; j++) {
                        tmp = usuario->libros[j + 1];
                        usuario->libros[j] = usuario->libros[j + 1];
                        usuario->libros[j + 1] = tmp;
                    }
                    // modifica la fecha de entrega
                    prestamo->fecha_devolucion = time(NULL);
                    // y lo marca como devuelto
                    prestamo->devuelto = 1;

                    usuario->disponibles++;

                    save_db(&prestamos, sizeof(prestamos), "prestamos.dat");
                    save_db(&usuarios, sizeof(usuarios), "usuarios.dat");
                }
            }
        }
    }

    eleccion = 0;
    if (usuario->tipo_usuario == ADMIN)
        eleccion = menu_administrador_como();

    // el administrador decidió entrar como administrador
    if (eleccion == 1) {
        while ((eleccion = menu_administrador_general()) != 7) {
            switch (eleccion) {
                case 1:
                    for (int i = 0; i < prestamos.actual; i++) {
                        prestamo = &prestamos.prestamos[i];

                        libro = find_book_by_id(prestamo->libro, &biblioteca);

                        diferencia = difftime(prestamo->fecha_devolucion, time(0));

                        printf("Nombre del libro: %s\n", libro.titulo);
                        printf("\tUsuario:            %s\n", find_user_by_id(prestamo->usuario, &usuarios).email);
                        printf("\tDía de préstamo:    %s", ctime(&prestamo->fecha_prestamo));
                        printf("\tDía de devolución:  %s", ctime(&prestamo->fecha_devolucion));
                        printf("\tDías restantes:     %ld\n", diferencia / 86400);
                        printf("\tDevuelto:           %s\n", (prestamo->devuelto) ? "Si" : "No");
                        printf("\n");
                    }

                    printf("\n\n");

                    break;

                case 2:
                    //Informe de usuarios dados de alta y libros en préstamo
                    memcpy(&usuarios_cpy, &usuarios, sizeof(usuarios));
                    insertion_sort(&usuarios_cpy);

                    for (int i = 0; i < usuarios_cpy.actual; i++) {
                        printf("Nombre del usuario: %s\n", usuarios_cpy.usuarios[i].nombre);
                        printf("\tNúmero de libros que ha pedido prestado: %d\n", 3 - usuarios_cpy.usuarios[i].disponibles);
                        printf("\n");
                    }

                    break;

                case 3:
                    //Se pueden dar de alta o de baja los libros
                    do {
                        eleccion = menu_alta_o_baja();

                        if (eleccion == 1){
                            register_book(&biblioteca, &autores, &categorias);
                        }

                        else if (eleccion == 2){
                            eleccion2 = 0;

                            for (int i = 0; i < biblioteca.actual; i++) {
                                libro = biblioteca.libros[i];
                                format_book(libro, &autores, &categorias, 1);

                                if (i % 5 == 0 && i != 0) {
                                    eleccion2 = menu_seleccionar_libros();

                                    if (eleccion2 == 2)
                                        baja_libro(usuario, &biblioteca);
                                    else if(eleccion2 == 3) {
                                        CLS;
                                        break;
                                    }
                                }
                            }
                            if (eleccion2 != 3) {
                                eleccion2 = menu_seleccionar_libros();

                                if (eleccion2 == 2)
                                    baja_libro(usuario, &biblioteca);
                                else if(eleccion2 == 3) {
                                    CLS;
                                }
                            }
                        }
                    } while(eleccion != 3);

                    break;

                case 4:
                    //baja de un cliente
                    menu_baja_de_usuario(email);

                    // busca el usuario para darlo de baja
                    found = 0;
                    for (int i = 0; i < usuarios.actual; i++) {
                        if (strcmp(usuarios.usuarios[i].email, email) == 0) {
                            found = 1;

                            sprintf(msg, "Se dió de baja el usuario %s por el administrador %s", email, usuario->nombre);
                            log_msg(msg);

                            // pone la bandera de activo en falso
                            usuarios.usuarios[i].activo = 0;

                            // guarda los usuarios
                            save_db(&usuarios, sizeof(usuarios), "usuarios.dat");

                            break;
                        }
                    }

                    if (!found)
                        printf("\tEl usuario especificado no existe\n");
                    else
                        printf("\tEl usuario fue exitosamente dado de baja\n");

                    break;

                case 5:
                    max = 0;
                    // obtiene la categoría mas popular
                    for (int i = 0; i < categorias.actual; i++) {
                        if (categorias.categorias[i].prestados > max) {
                            max = categorias.categorias[i].prestados;
                            categoria_popular = categorias.categorias[i];
                        }
                    }

                    printf("Categoría más popular: %s\n", categoria_popular.nombre);
                    printf("\tLibros prestados de la misma categoría: %d\n", categoria_popular.prestados);
                    printf("\n");

                    max = 0;
                    // obtiene el autor mas popular
                    for(int i = 0; i < autores.actual; i++) {
                        if (autores.autores[i].prestados > max) {
                            max = autores.autores[i].prestados;
                            autor_popular = autores.autores[i];
                        }
                    }

                    printf("Autor más popular: %s\n", autor_popular.nombre);
                    printf("\tLibros prestados del mismo autor: %d\n", autor_popular.prestados);
                    printf("\n");

                    max = 0;
                    // obtiene el libro mas popular
                    for (int i = 0; i < biblioteca.actual; i++) {
                        if (biblioteca.libros[i].prestamos > max) {
                            max = biblioteca.libros[i].prestamos;
                            libro = biblioteca.libros[i];
                        }
                    }

                    printf("Libro más popular:\n");
                    format_book(libro, &autores, &categorias, 0);
                    printf("\tCantidad de veces rentado: %d\n", libro.prestamos);
                    printf("\n");

                    break;

                case 6:
                    menu_ayuda();
                    break;

                default:
                    break;
            }
        }
    }

    // el administrador decidió como usuario o la cuenta es de tipo
    // usuario
    else if (eleccion == 2 || usuario->tipo_usuario == MORTAL) {
        while((eleccion_principal = menu_usuario()) != 6){
            switch(eleccion_principal) {
                case 1:
                    // accesar al catálogo de libros
                    while ((eleccion2 = menu_categorias()) != 4) {
                        eleccion = 0;

                        switch (eleccion2){
                            case 1:
                                for (int i = 0; i < biblioteca.actual; i++) {
                                    libro = biblioteca.libros[i];

                                    format_book(libro, &autores, &categorias, 0);

                                    if (i % 5 == 0 && i != 0) {
                                        eleccion = menu_funcion_agregar_libro(
                                            usuario, &biblioteca, &autores, &categorias, &prestamos);

                                        if (eleccion == 3) {
                                            CLS;
                                            break;
                                        }
                                    }
                                }
                                if (eleccion != 3) {
                                    eleccion = menu_funcion_agregar_libro(
                                        usuario, &biblioteca, &autores, &categorias, &prestamos);

                                    if (eleccion == 3)
                                        CLS;
                                }

                                save_db(&usuarios, sizeof(usuarios), "usuarios.dat");

                                break;

                            case 2:
                                printf("CATEGORÍAS EXISTENTES:\n\n");

                                for (int i = 0; i < categorias.actual; i++){
                                    printf("\t[%d] %s\n", i + 1, categorias.categorias[i].nombre);
                                }

                                printf("\n");

                                eleccion = validate_answer("Selecciona el genero: ", 1, categorias.actual + 1);
                                eleccion--;

                                CLS;

                                lookup_id = categorias.categorias[eleccion].id;
                                cat_count = 0;
                                for (int i = 0; i < biblioteca.actual; i++) {
                                    libro = biblioteca.libros[i];

                                    if (libro.categoria == lookup_id) {
                                        format_book(libro, &autores, &categorias, 0);

                                        if (cat_count % 5 == 0 && cat_count != 0) {
                                            eleccion = menu_funcion_agregar_libro(
                                                usuario, &biblioteca, &autores, &categorias, &prestamos);

                                            if (eleccion == 3) {
                                                CLS;
                                                break;
                                            }
                                        }

                                        cat_count++;
                                    }
                                }
                                if (eleccion != 3) {
                                    eleccion = menu_funcion_agregar_libro(
                                        usuario, &biblioteca, &autores, &categorias, &prestamos);

                                    if (eleccion == 3)
                                        CLS;
                                }

                                save_db(&usuarios, sizeof(usuarios), "usuarios.dat");

                                system("clear");
                                break;

                            case 3:
                                //más destacados
                                max = 0;
                                // obtiene la categoria mas popular
                                for (int i = 0; i < categorias.actual; i++) {
                                    if (categorias.categorias[i].prestados > max) {
                                        max = categorias.categorias[i].prestados;
                                        categoria_popular = categorias.categorias[i];
                                    }
                                }

                                printf("Categoría más popular: %s\n", categoria_popular.nombre);
                                printf("\tLibros prestados de la misma categoría: %d\n", categoria_popular.prestados);
                                printf("\n");

                                max = 0;
                                // obtiene el autor mas popular
                                for(int i = 0; i < autores.actual; i++) {
                                    if (autores.autores[i].prestados > max) {
                                        max = autores.autores[i].prestados;
                                        autor_popular = autores.autores[i];
                                    }
                                }

                                printf("Autor más popular: %s\n", autor_popular.nombre);
                                printf("\tLibros prestados del mismo autor: %d\n", autor_popular.prestados);
                                printf("\n");

                                max = 0;
                                // obtiene el libro mas popular
                                for (int i = 0; i < biblioteca.actual; i++) {
                                    if (biblioteca.libros[i].prestamos > max) {
                                        max = biblioteca.libros[i].prestamos;
                                        libro = biblioteca.libros[i];
                                    }
                                }

                                printf("Libro más popular:\n");
                                format_book(libro, &autores, &categorias, 0);
                                printf("\tCantidad de veces rentado: %d\n", libro.prestamos);
                                printf("\n");
                                break;

                            default:
                                break;
                        }
                    }
                    break;

                case 2:
                    // mostrar los libros en préstamo
                    printf("Libros prestados: %d\n", 3 - usuario->disponibles);

                    for (int i = 0; i < 3 - usuario->disponibles; i++) {
                        libro = find_book_by_id(usuario->libros[i], &biblioteca);
                        format_book(libro, &autores, &categorias, 0);
                    }

                    printf("\n\n");

                    break;

                case 3:
                    // devolver un libro
                    // imprime una lista de todos los libros que tiene prestados
                    printf("Libros prestados: %d\n", 3 - usuario->disponibles);

                    for (int i = 0; i < 3 - usuario->disponibles; i++) {
                        libro = find_book_by_id(usuario->libros[i], &biblioteca);
                        format_book(libro, &autores, &categorias, 0);
                    }

                    eleccion = menu_regresar_libro(nombre_libro);

                    // comprueba que tenga el libro en sus libros prestados
                    found = 0;
                    for (int i = 0; i < 3 - usuario->disponibles; i++) {
                        lookup_id = usuario->libros[i];

                        libro = find_book_by_id(lookup_id, &biblioteca);
                        if (eleccion == 1) {
                            if (strcmp(libro.titulo, nombre_libro) == 0) {
                                found = 1;
                                lookup_id = i;
                                break;
                            }
                        }
                        else if(eleccion == 2){
                            if (strcmp(libro.ISBN10, nombre_libro) == 0) {
                                found = 1;
                                lookup_id = i;
                                break;
                            }
                        }
                        else if(eleccion == 3){
                            if (strcmp(libro.ISBN13, nombre_libro) == 0) {
                                found = 1;
                                lookup_id = i;
                                break;
                            }
                        }
                    }

                    if (found) {
                        book_return(usuario, lookup_id, libro.id, &prestamos);
                        save_db(&usuarios, sizeof(usuarios), "usuarios.dat");

                        sprintf(msg, "El usuario %s devolvio el libro %s", usuario->nombre, libro.titulo);
                        log_msg(msg);
                    }
                    else {
                        printf("\tNo se encontró el libro especificado\n");
                    }

                    printf("\n\n");

                    break;

                case 4:
                    // agregar saldo
                    credito = menu_agregar_dinero();

                    sprintf(msg, "El usuario %s se agregó $%.2f", usuario->nombre, credito);

                    usuario->credito += credito;
                    credito += usuario->credito;

                    // recalcula el nuevo hash del credito
                    sprintf(a_credito, "%f", credito);
                    fastpbkdf2_hmac_sha256(a_credito, strlen(a_credito), usuario->c_hash,
                        128, 4096, hash, 256);

                    memcpy(usuario->c_hash, hash, 256);
                    save_db(&usuarios, sizeof(usuarios), "usuarios.dat");

                    printf("\tSaldo exitosamente guardado\n\n");

                    break;

                case 5:
                    // consultar saldo
                    printf("\n\tTu saldo es de: $%.2f pesos\n\n", usuario->credito);

                    break;

                default:
                    break;
            }
        }
    }

    return 0;
}
