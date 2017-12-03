/*
 * @utilites.h
 *
 * @brief Este archivo contiene todas las definiciones de las
 *        funciones que se encuentran en utilities.c
 *
 * @author Cristobal Liendo
 * @date 20/11/17
*/
#include <estructuras.h>

#define ADMIN 1
#define MORTAL 0

#ifndef UTILITIES_H
    #define UTILITIES_H

    int strip_char(char *source, char target);
    void log_msg(char *msg);
    void generate_salt(int length, char *salt);
    void disable_output();
    void enable_output();
    void disable_canonical();
    void enable_canonical();

    int add_user(ManejoUsuarios *usuarios, int type);
    void save_db(void *structure, unsigned int size, char *name);
    int legal(int *fecha_nac);
    int validate_answer(char *message, int start, int end);

    int add_book(Usuario *user, Biblioteca *bib, ManejoAutor *autores,
        ManejoCategoria *categorias, ManejoPrestamo *prestamos);;

    void register_book(Biblioteca *biblioteca, ManejoAutor *autores, ManejoCategoria *categorias);
    void insertion_sort(ManejoUsuarios *users);

    Libro find_book_by_id(int id, Biblioteca *bib);
    Usuario find_user_by_id(int id, ManejoUsuarios *users);
    Autor find_autor_by_id(int id, ManejoAutor *autores);
    Categoria find_categoria_by_id(int id, ManejoCategoria *categorias);

    int menu_funcion_agregar_libro(Usuario *user, Biblioteca *biblioteca,
        ManejoAutor *autores, ManejoCategoria *categorias, ManejoPrestamo *prestamos);
    void format_book(Libro libro, ManejoAutor *autores, ManejoCategoria *categorias, int admin);
    void baja_libro(Usuario *usuario, Biblioteca *biblioteca);
    void book_return(Usuario *user, int arr_id, int book_id,
        ManejoPrestamo *prestamos);
#endif
