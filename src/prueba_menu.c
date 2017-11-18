#include <stdio.h>
#include <menus.h>
#include <utilities.h>

int main() {
    char usuario[50], pwd[50], direccion[50];
    int fecha[3];

    menu_agregar_usuario(usuario, pwd, fecha, direccion);

    printf("Bienvenido de vuelta, %s.\n", usuario);
    printf("Tu contraseña es: %s\n", pwd);

    return 0;
}
