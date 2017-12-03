/*
 * @menus.h
 *
 * @brief Este archivo contiene todas las definiciones de las
 *        funciones que se encuentran en menus.c
 *
 * @author Cristobal Liendo
 * @date 20/11/17
*/

#define CLS system("clear")

#ifndef MENUS_H
    #define MENUS_H

    int menu_principal();
    int menu_agregar_usuario(char *nombre_usuario, char *contrasena,
        int *fecha, char *direccion, char *email, char *credito);
    void menu_acceso(char *email, char *password1);
    int menu_administrador_como();
    int menu_administrador_general();
    int menu_usuario();
    int menu_categorias();
    void menu_registrar_libro(char *titulo, char *autor, char *categoria,
        char *isbn10, char *isbn13, float *costo_libro, int *a_pub, char *editorial,
        int *paginas);
    void creditos();
    void menu_informe_prestamos();
    void menu_informe_usuarios();
    void menu_baja_de_usuario(char *usuario_baja);
    void menu_popular();
    void menu_ayuda();
    int menu_prestamo_libros();
    int menu_rentar_libro(char *name);
    int menu_alta_o_baja();
    int menu_seleccionar_libros();
    int menu_regresar_libro(char *name);
#endif
