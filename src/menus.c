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
#include <time.h>

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
    CLS;

    printf("Universidad Iberoamericana\n");
    printf("Fundamentos de Programacion\n\n");

    printf("Este programa fue desarrollado por:\n");
    printf("\tElena Ginebra\n");
    printf("\tGuillermo Ortega\n");
    printf("\tCristobal Liendo\n");

    printf("\n\nPresiona enter para entrar al sistema...");

    disable_canonical();
    getchar();
    enable_canonical();

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
    printf("[2] Crear una nueva cuenta\n");

    opcion_principal = validate_answer("Opción: ", 1, 2);
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

int menu_agregar_usuario (char *nombre_usuario, char *contrasena,
    int *fecha, char *direccion, char *email, char *credito) {
  
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

    if (!legal(fecha))
        return -1;

    printf("Ingresa tu correo: ");
    fgets(email, 50, stdin);

    strip_char(email, '\n');

    disable_output();
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
    enable_output();

    strip_char(contrasena1, '\n');
    strcpy(contrasena, contrasena1);

    printf("Ingresa el credito inicial: ");
    scanf("%s", credito);

    CLS;

    return 1;
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

void menu_acceso(char *email, char *password1) {
    printf("Ingresa tu correo: ");
    scanf("%s", email);
    getchar();

    disable_output();
    printf("Ingresa tu contraseña: ");
    fgets(password1, 50, stdin);
    enable_output();

    strip_char(password1, '\n');

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

    opcion_acceso_admin = validate_answer("Opción: ", 1, 2);
    CLS;

    return opcion_acceso_admin;
}

/*
 * Si el administrador escoge ingresar como admiistrador se le
 * desplegara la lista de opciones
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

    opcion_admin = validate_answer("Opción: ", 1, 7);
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
    printf("[4] Salir del sistema\n");

    opcion_usuario = validate_answer("Opción: ", 1, 4);
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
void menu_registrar_libro(char *titulo, char *autor, char *categoria,
    char *isbn10, char *isbn13, float *costo_libro, int *a_pub, char *editorial) {

    char char_autor, char_categoria;

    printf("ALTA DE LIBROS\n\n");
    printf("Registrar nuevo libro:\n\n");

    printf("\tIngresa el nombre del libro: ");
    fgets(titulo, 100, stdin);
    strip_char(titulo, '\n');

    printf("\tIngresa el autor del libro: ");
    fgets(autor, 100, stdin);
    strip_char(autor, '\n');
    
    printf("\tIngresa el género del libro: ");
    fgets(categoria, 50, stdin);
    strip_char(categoria, '\n');
    
    printf("\tIngresa el ISBN 10 del libro: ");
    fgets(isbn10, 15, stdin);
    strip_char(isbn10, '\n');

    printf("\tIngresa el ISBN 13 del libro: ");
    fgets(isbn13, 15, stdin);
    strip_char(isbn13, '\n');

    printf("\tIngresa la editorial del libro: ");
    fgets(editorial, 100, stdin);
    strip_char(editorial, '\n');
    
    printf("\tIngresa el año de publicación del libro: ");
    scanf("%d", a_pub);
    getchar();

    printf("\tIngresa el costo del libro: ");
    scanf("%f", costo_libro);
    getchar();

    CLS;

}


/*
 * Si el tipo de usuario es un administrador, puede ver un informe de todos 
 * los libros que se encuentran en préstamo
 * 
 * @author Elena Ginebra
 * @return void
 */
void menu_informe_prestamos() {
    printf("INFORME DE LIBROS EN PRÉSTAMO\n\n");
    printf("Número total de libros en préstamo 1\n\n");

    for (int i = 0; i < 1; i++) {
        printf("\tHarry Potter y la Piedra Filosofal\n");
        printf("\tFecha de préstamo: 12/11/2017\n");
        printf("\tFecha de devolución: 30/11/2017\n");
        printf("\n");
        printf("Días faltantes para su devolución: 3");
    }
  }


/*
 * Si el tipo de usuario es un administrador, puede ver un informe de todos
 * los usuarios que se encuentran registrados en la base de datos
 *
 * @author Elena Ginebra
 * @return void
 */
void menu_informe_usuarios() {
    printf("INFORME DE USUARIOS DADOS DE ALTA\n");

    for (int i = 0; i < 1; i++){
        printf("\tElena Ginebra\n");
        printf("\telena@chapterchicks.com\n");
        printf("\tLibros prestados: 1\n");
        printf("\tAdministradora\n");
        printf("\tActivo\n");
    }
}


/* 
 * Si el tipo de usuario es un administrador, puede dar de baja
 * un usuario que se encuentre registrado en la base de datos
 * 
 * @author Elena Ginebra, Cristobal Liendo
 * @return void 
 */
void menu_baja_de_usuario(char *usuario_baja){
    printf("Ingresa el correo del usuario: ");
    scanf("%s", usuario_baja);
    getchar();

    CLS;
}


/*
 * Si el tipo de usuario es un administrador, puede mostrar
 * el autor, la categoría y el título más popular
 *
 * @author Elena Ginebra
 * @return void
 */
void menu_popular(){
    printf("MÁS DESTACADOS\n\n");
    printf("\tCategoría más popular: Fantasía\n");
    printf("\tTítulo más popular: Harry Potter y la Piedra Filosofal\n");
    printf("\tAutor más popular: J. K. Rowling\n");
    printf("\n");
}


/*
 * Si el tipo de usuario es un administrador, puede mostrar un
 * menú de ayuda al administrador donde se despliegan opciones distintas
 * dependiendo del área donde necesite ayuda, puede ser ayuda para
 * registrar usuarios, catálogo de libros, préstamos y devoluciones
 * ó regresar al menú principal.
 *
 * @author Elena Ginebra
 * @return void
 */
void menu_ayuda(){
    int opcion_ayuda;

    CLS;
    
    do{
        printf("AYUDA\n\n");
        printf("Selecciona el número correspondiente para el tipo de información que necesitas: \n");
        printf("[1] Registros de usuarios\n");
    printf("[2] Catálogo de libros\n");
        printf("[3] Preśtamos y devoluciones.\n"); 
        printf("[4] Salir de ayuda\n");
        printf("Opción:");
        scanf("%d", &opcion_ayuda);
        getchar();
        printf("\n\n");

        if(opcion_ayuda==1) {
        printf("El sistema debe permitir las siguientes facilidades al usuario/cliente del servicio:\n");
        printf("\t1.- Pre-acceso para auto-registrarse como usuario del servicio, en este módulo permitirá a un usuario darse de alta con sus datos fundamentales:\n");
        printf("\t\t• Nombre completo\n\t\t• Dirección\n\t\t• Fecha de nacimiento (tendrá que tener al menos 18 años de edad cumplidas)\n\t\t• Correo electrónico\n");
        printf("\t2.- Acceso como usuario registrado al catálogo de libros para selección de un máximo de 3 libros.\n");
        printf("\t3.- Devolución de libros\n");
        printf("Una vez creada un usuario, estará activo por \"default\" sin embargo ésta se puede dar de baja a partir del menú general de administrador o lo puede realizar el mismo usuario si así lo desea.\n");
        printf("Cada usuario deberá tener un correo único y no podrá registrarse más de una sola vez.\n");
        printf("\nSi el administrador utiliza el modo de ejecucion que implica usar el parámetro\"-usu\" despliega el listado de todos los usuarios del servicio catalogados y muestra su alta y baja.\n");   
            printf("El administador no tendrá acceso a las contraseñas de los usuarios. Tampoco podrá acceder ni modificar el crédito de ninguno de ellos\n\n");
        }
        
        else if(opcion_ayuda == 2) {
            printf("Una categoría de libros consiste en hacer una selección que agrupa todos los libros que tratan del mismo tema o uno similar para así facilitar y sugerir al usuario libros que le convengan leer, dependiendo de sus gustos e intereses.\n");
            printf("Las categorías se crean desde que uno registra el libro y se agrupan de manera automatizada con todos los libros que hayan sido ingresados con la misma categoría.\n");;
        printf("El usuario tendrá acceso a cada una de éstas categorías y podrá elegir cualquier libro de ellos (con la condición de que no tenga ya tres libros rentados en su cuenta al momento de querer pedir prestado.\n)");
        printf("Un libro NO puede pertenecer a más de una categoría\n\n");
        }
        
        else if(opcion_ayuda == 3) {
            printf("Cada usuario tiene acceso a pedir prestado un máximo de 3 libros en un determinado momento (al mismo tiempo).\n");
            printf("Los libros se pueden prestar hasta un máximo de 30 días, la cuenta empieza desde el día que se pidió prestado hasta que termine este mismo periodo.\n");
        printf("Si el usuario termina un libro antes de la fecha de devolución ó desea regresarlo antes del periodo de préstamo, tendrá la opción de hacerlo.\n");
            printf("\nSi el administrador utiliza el modo de ejecucion que implica usar \"-c\", se despliega un informe de todos los usuarios y libros correspondientes que se encuentran en su posesión en ese momento determinado.\n\n");
        }
    } while (opcion_ayuda != 4);
}

/*
 * Muestra el menu de categorias para permitirle al usuario una mejor
 * busqueda de los libros que desea rentar
 *
 * @author Elena Ginebra
 * @return int
*/
int menu_categorias() {
    int opcion_categorias;

    printf("¿Qué quieres hacer?\n");
    printf("[1] Mostrar todo el catálogo de libros\n");
    printf("[2] Elegir de las categorías existentes\n");
    printf("[3] Mostrar los libros más destacados\n");
    printf("[4] Mostrar sugerencias\n");
    printf("[5] Salir de biblioteca\n");

    opcion_categorias = validate_answer("Opción: ", 1, 5);
    CLS;

    return opcion_categorias;
}

/*
 * Este menu se muestra cada 5 libros para preguntarle al usuario
 * si desea seguir, rentar un libro o salir de los libros
 *
 * @author Cristobal Liendo
 * @return int
*/
int menu_prestamo_libros() {
    printf("¿Qué quieres hacer?\n");
    printf("[1] Seguir con la lista\n");
    printf("[2] Rentar un libro\n");
    printf("[3] Salir\n");

    return validate_answer("Opción: ", 1, 3);
}

/*
 * Esta funcion sirve para desplegar el menu que pregunta el libro a
 * prestar. Puede ser por nombre, isbn 10 e isbn 13.
 *
 * regresa un 1 si es nombre, 2 si es isbn 10 y 3 si es isbn 13
 *
 * @author Cristobal Liendo
 * @param *name  nombre del libro
 * @return int
*/

int menu_rentar_libro(char *name) {
    int eleccion;

    printf("¿Cómo deseas buscar el libro?\n");
    printf("[1] Por nombre\n");
    printf("[2] Por ISBN 10\n");
    printf("[3] Por ISBN 13\n");

    eleccion = validate_answer("Opción: ", 1, 3);

    if (eleccion == 1)
        printf("Ingresa el nombre del libro: ");
    else if (eleccion == 2)
        printf("Ingresa el ISBN 10 del libro: ");
    else if (eleccion == 3)
        printf("Ingresa el ISBN 13 del libro: ");

    fgets(name, 100, stdin);
    strip_char(name, '\n');

    return eleccion;
}

/*                           
* Este menu le pregunta al administrador si desea dar de                                                                                                                  
* alta un libro o dar un libro de baja
*                                                                                                                                                                               
* @author Elena Ginebra                                                                                                                                                    
* @return int                                                                                                                                                             
*/
int menu_alta_o_baja(){
  
  int opcion_alta_o_baja;
  
      printf("¿Qué quieres hacer?\n");
      printf("[1] Alta de un libro\n");
      printf("[2] Baja de un libro\n");
      printf("[3] Salir\n");
      printf("Opción: ");

  do {
    scanf("%d", &opcion_alta_o_baja);
    getchar();
  } while (opcion_alta_o_baja<1 || opcion_alta_o_baja >3);

  CLS;
  
    return opcion_alta_o_baja;
}

/*                                                                                        
 * Si el tipo de usuario es un administrador, puede dar de baja                           
 * un libro que se encuentre registrado en la base de datos                             
 *                                                                                        
 * @author Elena Ginebra
 * @return void                                                                           
 */
void menu_baja_de_libros(char *libro_baja) {
  printf("Ingresa el titulo del libro: ");
  scanf("%s", libro_baja);
  getchar();

  CLS;
}

