/*
 * @menus.h
 *
 * @brief Este archivo contiene todas las definiciones de las
 *        funciones que se encuentran en menus.c
 *
 * @author Cristobal Liendo
 * @date 20/11/17
*/

#ifndef MENUS_H
    #define MENUS_H

    int menu_principal();
    int menu_agregar_usuario(char *nombre_usuario, char *contrasena,
        int *fecha, char *direccion);
    int menu_acceso(char *correo, char *password1, char *password2);
    int menu_administrador_como();
    int menu_administrador_general();
    int menu_usuario();
    void menu_registrar_libro(char *nombre_libro, char *nombre_autor, char *categoria, char *isbn, float *costo_libro);
#endif
