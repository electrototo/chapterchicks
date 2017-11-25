/*
 * @utilites.h
 *
 * @brief Este archivo contiene todas las definiciones de las
 *        funciones que se encuentran en utilities.c
 *
 * @author Cristobal Liendo
 * @date 20/11/17
*/

#ifndef UTILITIES_H
    #define UTILITIES_H

    int strip_char(char *source, char target);
    void log_msg(char *msg);
    void generate_salt(int length, char *salt);
#endif
