/*
 * @utilities.c
 *
 * @brief
 *
 * @author Cristobal Liendo
 * @date 20/11/17
*/

#include <utilities.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *log_file, *rand_file;

/*
 * Esta funcion recibe como parametro un arreglo de caracteres
 * y remplaza la primera ocurrencia del caracter 'b' en 'a'
 * con un caracter nulo. 
 * Se va a utilizar para quitar principalmente la nueva linea
 * que se obtiene al utilizar fgets().
 * Regresa un 1 si se encontro el caracter y un 0 si no
 *
 * @author Cristobal Liendo
 * @param *source      la cadena de caracteres en la que se va a buscar
 * @param target       el caracter a sustituir con '\0'
 * @return int
*/

int strip_char(char *source, char target) {
    int status = 0;

    while (*source) {
        if (*source == target) {
            *source = '\0';
            status = 1;
        }

        *source++;
    }

    return status;
}

/*
 * Esta funcion recibe como parametro una cadena de texto para
 * poder registar esa cadena en un archivo que se llama
 * actividades.log
 * Sirve para poder llevar una bitacora de todas las acciones
 * que el administrador realiza
 *
 * @author Cristobal Liendo
 * @param *msg    Es el mensaje que se quiere guardar en "actividades.log"
 * @return void
*/

void log_msg(char *msg) {
    char timestamp[50];

    time_t cur_time;
    struct tm *loc_time;

    cur_time = time (NULL);
    loc_time = localtime (&cur_time);

    log_file = fopen("bitacora.log", "a");
    strftime(timestamp, 50, "[%d/%b/%C:%T] ", loc_time);

    fprintf(log_file, "%s", timestamp);
    fprintf(log_file, "%s\n", msg);
    fclose(log_file);
}

/*
 * Esta funcion genera de manera aleatoria un salt para
 * poder generar el hash de la contrasena mediante
 * el algoritmo de pbkdf2
 *
 * @author Cristobal Liendo
 * @param  length    Es la longitud en bytes del salt que se quiere generar
 * @param  *salt     Es la direccion en memoria donde se guardan @p length bytes
*/

void generate_salt(int length, char *salt) {
    rand_file = fopen("/dev/urandom", "r");
    fread(salt, length, 1, rand_file);
    fclose(rand_file);
}
