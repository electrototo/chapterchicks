/*
 * @file estructuras.h
 *
 * @brief Este archivo contiene las definiciones de
 *        las estructuras que se van a utilizar en 
 *        el programa aleer
 *
 * @author Cristobal Liendo I
 * @date 22/11/2017
*/

#ifndef ESTRUCTURAS_H
    #define ESTRUCTURAS_H
    typedef struct {
        char nombre[50];
        int id;
        int prestados;
    } Autor;

    typedef struct {
        int actual;
        Autor autores[70];
    } ManejoAutor;

    typedef struct {
        char nombre[50];
        int id;
        int prestados;
    } Categoria;

    typedef struct {
        int actual;
        Categoria categorias[70];
    } ManejoCategoria;

    typedef struct {
        int autor;
        int categoria;

        char editorial[100];
        char titulo[50];
        char ISBN13[14];
        char ISBN10[11];
        float costo;
        int activo;
        int prestamos;
        int a_pub;
        int id;
    } Libro;

    typedef struct {
        int actual;
        Libro libros[70];
    } Biblioteca;

    typedef struct {
        int disponibles;
        int tipo_usuario;
        int activo;
        int fecha_nacimiento[3];
        int edad;
        char nombre[100];
        char direccion[100];
        char email[100];
        char contrasena[256];
        char salt[128];
        float credito;

        char c_hash[256];
        char c_salt[128];

        int id;
    } Usuario; 

    typedef struct {
        Usuario usuarios[50];
        int actual;
    } ManejoUsuarios;

    typedef struct {
        int libro;
        int usuario;
        int fecha_prestamo;
        int fecha_devolucion;
    } Prestamo;
#endif
