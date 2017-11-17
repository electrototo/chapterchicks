#include <stdio.h>
#include <menus.h>

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

int menu_agregar_usuario(char *nombre_usuario, char *contrasena) {
    char contrasena1[50];
    char contrasena2[50];

    printf("Ingresa tu nombre completo: ");
    scanf("%s", nombre_usuario);

    printf("Ingresa tu contraseña: ");
    scanf("%s", contrasena1);

    printf("Vuelve a ingresar tu contraseña: ");
    scanf("%s", contrasena2);
}

int menu_acceso(char *correo,char *password) {
    printf("Ingresa tu correo:\n ");
    scanf("%s",correo);
    printf("Ingresa tu contraseña: ");
    scanf("%s",password);
}

int menu_administrador_como() {
    int opcion_acceso_admin;

    printf("¿Deseas ingresar como administrador o como usuario?\n");
    printf("[1] Administrador\n[2] Usuario\n");

    do{

        printf("Opción: ");
        scanf("%d",&opcion_acceso_admin);
        getchar();

    } while(opcion_acceso_admin < 1 || opcion_acceso_admin > 2);
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
}
  
int menu_usuario() {
    int opcion_usuario;

    printf("¿Qué quieres hacer?\n");
    printf("[1] Accesar al catálogo de libros\n");
    printf("[2] Mostrar libros en préstamo\n");
    printf("[3] Devolución de libros\n");

    do{
        printf("Opción: ");
        scanf("%d",&opcion_usuario);
        getchar();
    } while(opcion_usuario < 1 || opcion_usuario > 3);
}

int main() {
    menu_principal();
    menu_acceso();
    menu_administrador_como();
    menu_administrador_general();
    menu_usuario();
}
