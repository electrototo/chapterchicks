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

/*
 * Esta función imprime los nombres de los programadores
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
 * Es el menú que se imprime despues de haber mostrado
 * los nombres de los programadores. Hay dos opciones:
 * entrar al sistema o el auto registro para usuarios 
 * nuevos que quieran usar el sistema.
 * El sistema entra en un ciclo hasta que el usuario
 * haya ingresado una opción válida
 *
 * @author Guillermo Ortega
 * @return 1 o 2, dependiendo de la elección del usuario
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
 * Este menú será usado para que el usuario pueda registrarse.
 * La contraseña la ingresa el usuario, debido a que es una
 * mala práctica mandar contraseñas por correo debido a que 
 * estas deben ir en texto claro.
 * La función tambien verifica que ambas contraseñas coincidan,
 * si no coinciden entra en un ciclo hasta que el usuario haya
 * ingresado unas contraseñas que coincidan
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
 * Esta función recibe como parámetros dos direcciones de memoria
 * a las que se van a guardar el correo y la contraseña proporcionadas
 * por el usuario.
 * Su función principal es preguntarle al usuario su correo y su
 * contrasena
 *
 * @author Cristobal Liendo, Elena Ginebra, Guillermo Ortega
 * @param  *correo    Significa donde se desea guardar el correo
 *                    ingresado por el usuario
 * @param  *password  Es donde se desea guardar la contrasena
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
 * este menú para que pueda seleccionar la modalidad en la que desea
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
 * Si el administrador escoge ingresar como administrador se le
 * desplegará la lista de opciones
 * Regresa la opción que sea escogida y sigue preguntando mientras
 * que la opción ingresada no esté entre las opciones disponibles
 *
 * @author Guillermo Ortega, Elena Ginebra, Cristobal Liendo
 * @return int
*/
int menu_administrador_general() {
    int opcion_admin;

    printf("¿Qué quieres hacer?\n");
    printf("[1] Informe de libros en préstamo\n");
    printf("[2] Informe de usuarios dados de alta\n");
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
 * Si el tipo de usuario es un usuario o un administrador escoge ingresar como
 * usuario, este menú despliega las acciones disponibles 
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
    printf("[4] Agregar saldo\n");
    printf("[5] Consultar saldo\n");
    printf("[6] Salir del sistema\n");

    opcion_usuario = validate_answer("Opción: ", 1, 6);
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
    char *isbn10, char *isbn13, float *costo_libro, int *a_pub, char *editorial,
    int *paginas) {

    char char_autor, char_categoria;

    printf("ALTA DE LIBROS\n\n");
    printf("Registrar nuevo libro:\n\n");

    printf("\tNombre del libro:     ");
    fgets(titulo, 100, stdin);
    strip_char(titulo, '\n');

    printf("\tAutor del libro:      ");
    fgets(autor, 100, stdin);
    strip_char(autor, '\n');
    
    printf("\tGénero del libro:     ");
    fgets(categoria, 50, stdin);
    strip_char(categoria, '\n');
    
    printf("\tISBN 10 del libro:    ");
    fgets(isbn10, 15, stdin);
    strip_char(isbn10, '\n');

    printf("\tISBN 13 del libro:    ");
    fgets(isbn13, 15, stdin);
    strip_char(isbn13, '\n');

    printf("\tEditorial del libro:  ");
    fgets(editorial, 100, stdin);
    strip_char(editorial, '\n');
    
    printf("\tAño de publicación:   ");
    scanf("%d", a_pub);
    getchar();

    printf("\tCosto del libro:      ");
    scanf("%f", costo_libro);
    getchar();

    printf("\tPaginas:              ");
    scanf("%d", paginas);
    getchar();

    CLS;
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
    
    do {
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
            printf("Una vez creado un usuario, estará activo por \"default\" sin embargo ésta se puede dar de baja a partir del menú general de administrador o lo puede realizar el mismo usuario si así lo desea.\n");
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
 * Muestra el menú de categorías para permitirle al usuario una mejor
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
    printf("[4] Salir de biblioteca\n");

    opcion_categorias = validate_answer("Opción: ", 1, 4);
    CLS;

    return opcion_categorias;
}

/*
 * Este menú se muestra cada 5 libros para preguntarle al usuario
 * si desea seguir, rentar un libro o salir de los libros
 *
 * @author Cristobal Liendo
 * @return int
*/
int menu_prestamo_libros() {
    int eleccion;

    printf("¿Qué quieres hacer?\n");
    printf("[1] Seguir con la lista\n");
    printf("[2] Rentar un libro\n");
    printf("[3] Salir\n");

    eleccion = validate_answer("Opción: ", 1, 3);

    if (eleccion == 3 || eleccion == 1)
        CLS;

    return eleccion;
}

/*
 * Esta funcion sirve para desplegar el menú que pregunta el libro a
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

    printf("\n¿Cómo deseas buscar el libro?\n");
    printf("[1] Por nombre\n");
    printf("[2] Por ISBN 10\n");
    printf("[3] Por ISBN 13\n");

    eleccion = validate_answer("Opción: ", 1, 3);

    if (eleccion == 1)
        printf("\n\tIngresa el nombre del libro: ");
    else if (eleccion == 2)
        printf("\n\tIngresa el ISBN 10 del libro: ");
    else if (eleccion == 3)
        printf("\n\tIngresa el ISBN 13 del libro: ");

    fgets(name, 100, stdin);
    strip_char(name, '\n');

    return eleccion;
}

/*
 * Esta funcion sirve para desplegar el menú que pregunta el libro a
 * regresar. Puede ser por nombre, isbn 10 e isbn 13.
 *
 * es muy parecida a la anterior, con diferencia que cambia el texto
 *
 * regresa un 1 si es nombre, 2 si es isbn 10 y 3 si es isbn 13
 *
 * @author Cristobal Liendo, Elena Ginebra
 * @param *name  nombre del libro
 * @return int
*/

int menu_regresar_libro(char *name) {
    int eleccion;

    printf("\n¿Cómo deseas regresar el libro?\n");
    printf("[1] Por nombre\n");
    printf("[2] Por ISBN 10\n");
    printf("[3] Por ISBN 13\n");
    printf("[4] Regresar a menú principal\n");

    eleccion = validate_answer("Opción: ", 1, 4);

    if (eleccion == 1)
        printf("\n\tIngresa el nombre del libro: ");
    else if (eleccion == 2)
        printf("\n\tIngresa el ISBN 10 del libro: ");
    else if (eleccion == 3)
        printf("\n\tIngresa el ISBN 13 del libro: ");

    fgets(name, 100, stdin);
    strip_char(name, '\n');

    CLS;

    return eleccion;
}

/*                           
* Este menú le pregunta al administrador si desea dar de
* alta un libro o dar un libro de baja
*
* @author Elena Ginebra
* @return int
*/
int menu_alta_o_baja(){
    int resultado;

    printf("¿Qué quieres hacer?\n");
    printf("[1] Alta de un libro\n");
    printf("[2] Baja de un libro\n");
    printf("[3] Salir\n");

    resultado = validate_answer("Opción: ", 1, 3);

    CLS;
  
    return resultado;
}

/*
 * Este menú sirve para preguntar al usuario si quiere seguir imprimiendo mas
 * libros, dar de baja un libro o salirse. 
 *
 * @author Cristobal Liendo
*/

int menu_seleccionar_libros() {
    int resultado;
    printf("\n¿Qué quieres hacer?\n");
    printf("[1] Continuar con la lista\n");
    printf("[2] Dar de baja un libro\n");
    printf("[3] Regresar\n");

    resultado = validate_answer("Opción: ", 1, 3);

    return resultado;
}

/* 
 * Este menu sirve para poder preguntar el saldo que se desa agregar.
 * Puede ser un valor entre $10 y $3000 
 *
 * @author Cristobal Liendo
 * @return float
*/

int menu_agregar_dinero() {
    float dinero;

    do {
        printf("\n\tIngresa el dinero (entre $10 y $3000): ");
        scanf("%f", &dinero);
    } while (dinero < 10 || dinero > 3000);

    return dinero;
}
