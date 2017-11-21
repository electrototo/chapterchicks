/*
 * @menus.c
 *
 * @brief
 *
 * @author Guillermo Ortega, Elena Ginebra, Cristobal Liendo
 * @date 20/11/17
*/

#include <stdio.h>
#include <string.h>
#include <menus.h>
#include <utilities.h>

int menu_principal() {
    int opcion_principal;
    printf("BIENVENIDO\n\n");
    printf("[1] Entrar\n");
    printf("[2] Agregar nueva cuenta\n");

    do {
        printf("Opción: ");
        scanf("%d",&opcion_principal);
        getchar();

    } while(opcion_principal < 1 || opcion_principal > 2);

    return opcion_principal;
}

int menu_agregar_usuario (char *nombre_usuario, char *contrasena,
        int *fecha, char *direccion) {

    char contrasena1[50];
    char contrasena2[50];

    int wrong = 0;

    printf("Ingresa tu nombre completo: ");
    fgets(nombre_usuario, 50, stdin);

    strip_char(nombre_usuario, '\n');

    printf("Ingresa tu direccion: ");
    fgets(direccion, 50, stdin);

    strip_char(direccion, '\n');

    printf("Ingresa tu fecha de nacimiento [dd/mm/aaaa]: ");
    scanf("%d/%d/%d", &fecha[0], &fecha[1], &fecha[2]);
    getchar();

    do {
        if (!wrong)
            wrong = 1;
        else
            printf("\tLas contraseñas no coinciden\n");

        printf("Ingresa tu contraseña: ");
        fgets(contrasena1, 50, stdin);

        printf("Vuelve a ingresar tu contraseña: ");
        fgets(contrasena2, 50, stdin);
    } while (strcmp(contrasena1, contrasena2) != 0);

    strip_char(contrasena1, '\n');
    strcpy(contrasena, contrasena1);
}

/*
 * el problema de esta funcion es que si usamos scanf()
 * para la contraseña, la contraseña no puede tener un
 * espacio, por lo tanto tenemos que usar un fgets(),
 * sin embargo si usamos un fgets, tenemos que quitar el
 * ultimo caracter, el cual es una nueva linea ('\n')
*/
int menu_acceso(char *correo, char *password1, char *password2) {
    printf("Ingresa tu correo:\n ");
    scanf("%s", correo);
    getchar();

    printf("Ingresa tu contraseña: ");
    fgets(password1, 50, stdin);

    if (strcmp(password1, password2) != 0) {
        printf("\tLa contraseña y/o el nombre de usuario son incorrectos\n");

        return 0;
    }

    return 1;
}

int menu_administrador_como() {
    int opcion_acceso_admin;

    printf("¿Deseas ingresar como administrador o como usuario?\n");
    printf("[1] Administrador\n");
    printf("[2] Usuario\n");

    do{

        printf("Opción: ");
        scanf("%d", &opcion_acceso_admin);
        getchar();

    } while(opcion_acceso_admin < 1 || opcion_acceso_admin > 2);

    return opcion_acceso_admin;
}

int menu_administrador_general() {
    int opcion_admin;

    printf("¿Qué quieres hacer?\n");
    printf("[1] Informe de libros en préstamo\n");
    printf("[2] Informe de usuarios dados de alta y libros en préstamo\n");
    printf("[3] Alta y baja de libros\n");
    printf("[4] Baja de un cliente\n");
    printf("[5] Obtener la categoría, autor y el título más popular\n");
    printf("[6] Ayuda\n");
    printf("[7] Salida del sistema\n");

    do {

        printf("Opción: ");
        scanf("%d",&opcion_admin);
        getchar();

    } while(opcion_admin < 1 || opcion_admin > 7);

    return opcion_admin;
}
  
int menu_usuario() {
    int opcion_usuario;

    printf("¿Qué quieres hacer?\n");
    printf("[1] Accesar al catálogo de libros\n");
    printf("[2] Mostrar libros en préstamo\n");
    printf("[3] Devolución de libros\n");

    do{
        printf("Opción: ");
        scanf("%d", &opcion_usuario);
        getchar();
    } while(opcion_usuario < 1 || opcion_usuario > 3);

    return opcion_usuario;
}

void menu_registrar_libro(char *nombre_libro, char *nombre_autor, char *categoria, char *isbn, float *costo_libro) {
    printf("Registrar nuevo libro:\n");

    printf("Ingresa el título completo del libro: ");
    fgets(nombre_libro, 50, stdin);

    printf("Ingresa el nombre completo del autor: ");
    fgets(nombre_autor, 50, stdin);

    printf("Ingresa la categoría del libro: ");
    fgets(categoria, 50, stdin);

    printf("Ingresa el ISBN del libro: ");
    fgets(isbn, 50, stdin);

    printf("Ingresa el costo del libro: ");
    scanf("%f", costo_libro);
}
