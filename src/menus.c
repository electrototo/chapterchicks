/*
 * @menus.c
 *
 * @brief
 *
 * @author Guillermo Ortega, Elena Ginebra, Cristobal Liendo
 * @date 20/11/17
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <menus.h>
#include <utilities.h>

#define CLS system("clear")

/*
 * Esta funcion imprime los nombres de los programadores
 * cada vez que se inicie el programa
 *
 * @author Cristobal Liendo
 * @return void
*/

void creditos() {
    printf("Universidad Iberoamericana\n");
    printf("Fundamentos de Programacion\n\n");

    printf("Este programa fue desarrollado por:\n");
    printf("\tElena Ginebra\n");
    printf("\tGuillermo Ortega\n");
    printf("\tCristobal Liendo\n");

    printf("\n\nPresiona cualquier tecla para salir...");

    getchar();

    CLS;
}

/*
 * Es el menu que se imprime despues de haber mostrado
 * los nombres de los programadores. Hay dos opciones:
 * entrar al sistema o el auto registro para usuarios 
 * nuevos que quieran usar el sistema.
 * El sistema entra en un ciclo hasta que el usuario
 * haya ingresado una opcion valida
 *
 * @author Guillermo Ortega
 * @return 1 o 2, dependiendo de la eleccion del usuario
*/
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

    CLS;

    return opcion_principal;
}

/*
 * Este menu sera usado para que el usuario pueda registrarse.
 * La contrasena la ingresa el usuario, debido a que es una
 * mala practica mandar contrasenas por correo debido a que 
 * estas deben ir en texto claro.
 * La funcion tambien verifica que ambas contrasenas coincidan,
 * si no coinciden entra en un ciclo hasta que el usuario haya
 * ingresado unas contrasenas que coincidan
 *
 * @author Guillermo Ortega, Elena Ginebra, Cristobal Liendo
 * @return void
*/

void menu_agregar_usuario (char *nombre_usuario, char *contrasena,
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

    CLS;
}

/*
 * Esta funcion recibe como parametros dos direcciones de memoria
 * a las que se van a guardar el correo y la contrasena proporcionadas
 * por el usuario.
 * Su funcion principal es preguntarle al usuario su correo y su
 * contrasena
 *
 * @author Cristobal Liendo, Elena Ginebra, Guillermo Ortega
 * @param  *correo    Significa donde se desea guardar el correo
 *                    ingresado por el usuario
 * @param  *password  Es a donde se desea guardar la contrasena
 *                    proporcionada por el usuario
 * @return void
*/

void menu_acceso(char *correo, char *password1) {
    printf("Ingresa tu correo: ");
    scanf("%s", correo);
    getchar();

    printf("Ingresa tu contraseña: ");
    fgets(password1, 50, stdin);

    CLS;
}

/*
 * Si el tipo de usuario es un administrador, se le va a desplegar
 * este menu para que pueda seleccionar la modalidad en la que desea
 * entrar al sistema.
 * Regresa un 1 si quiere entrar como administrador y un 2 si es que
 * desea ingresar como usuario normal
 *
 * @author Guillermo Ortega, Elena Ginebra, Cristobal Liendo
 * @return int
*/

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

    CLS;

    return opcion_acceso_admin;
}

/*
 * Si el administrador escoge ingresar como admiistrador se le
 * deplegara la lsta de opciones
 * Regresa la opción que sea escogida y sigue preguntando mientras
 * que la opcion ingresada no esté entre las opciones disponibles
 *
 * @author Guillermo Ortega, Elena Ginebra, Cristobal Liendo
 * @return int
*/
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

    CLS;

    return opcion_admin;
}

/*
 * Si el tipo de usuario es un usuario o un administrados escoge ingresar como
 * usuario, este menu despliega las acciones disponibles 
 * para un usuario
 * Regresa la opción escogida por el usuario y sigue preguntando por esta mientras
 * que la opción ingresada no sea válida.
 *
 * @author Guillermo Ortega, Elena Ginebra, Cristobal Liendo
 * @return int
*/
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

    CLS;

    return opcion_usuario;
}

/*
 * Si el tipo de usuario es un administrador, puede escoger registrar un libro
 * nuevo, este menú le pregunta los datos del libro al administrador para poder guardarlo.
 *
 * @author Guillermo Ortega, Elena Ginebra, Cristobal Liendo
 * @param *nombre_libro      el nombre del libro
 * @param *nombre_autor      el nombre del autor del libro
 * @param *categoria         la categoría/género del libro
 * @param *isbn              el isbn del libro
 * @param *costo_libro       el costo del libro
 * @return void
*/
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

    CLS;
}


void menu_informe_prestamos ()
{
  int total_libros_prestamo;

  printf("Número total de libros en préstamo%d\n\n", total_libros_prestamo);

  for (int i=1; i<=total_libros_prestamo; i++)
    {

      printf("LIBRO #%d\n", i);
      printf("Fecha de préstamo: \n");
      printf("Fecha de devolución: \n");
      printf("Días restantes para la devolucón: ");
    }
  
}
