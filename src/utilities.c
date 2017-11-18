#include <utilities.h>

/*
 * Esta funcion recibe como parametro un arreglo de caracteres
 * y remplaza la primera ocurrencia del caracter 'b' en 'a'
 * con un caracter nulo. 
 * Se va a utilizar para quitar principalmente la nueva linea
 * que se obtiene al utilizar fgets().
 * Regresa un 1 si se encontro el caracter y un 0 si no
 *
 * @autor Cristobal Liendo
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