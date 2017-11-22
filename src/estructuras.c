/*
 * @file estructuras.c
 *
 * @brief Este archivo contiene todas las estructuras que
 *        se van a utilizar en el programa aleer
 *
 * @author Cristobal Liendo I
 * @date 22/11/2017
*/

#include <estructuras.h>

struct Autor {
    char nombre[50];
    int prestados;
};

struct Categoria {
    char nombre[50];
    int prestados;
};

struct Libro {
    int autor;
    int categoria;

    char titulo[50];
    char ISBN13[14];
    char ISBN10[11];
    int costo;
    int activo;
    int prestamos;
    int a_pub;
};

struct Usuario {
    int disponibles;
    int tipo_usuario;
    int activo;
    int fecha_nacimiento[3];
    char nombre[100];
    char direccion[100];
    char email[100];
    char contrasena[258];
    int id;
}; 

struct Prestamo {
    int libro;
    int usuario;
    int fecha_prestamo;
    int fecha_devolucion;
};
