#ifndef MENUS_H
    #define MENUS_H

    int menu_principal();
    int menu_agregar_usuario(char *nombre_usuario, char *contrasena,
        int *fecha, char *direccion);
    int menu_acceso(char *correo, char *password1, char *password2);
    int menu_administrador_como();
    int menu_administrador_general();
    int menu_usuario();
#endif