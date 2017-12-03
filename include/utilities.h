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
#endif
