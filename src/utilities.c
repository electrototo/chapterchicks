/*
 * @utilities.c
 *
 * @brief
 *
 * @author Cristobal Liendo
 * @date 20/11/17
*/

#include <utilities.h>
#include <estructuras.h>
#include <menus.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // STDIN_FILENO
#include <time.h>
#include <termios.h>
#include <string.h>

#include <fastpbkdf2.h>

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
 * @return void
*/

void generate_salt(int length, char *salt) {
    rand_file = fopen("/dev/urandom", "r");
    fread(salt, length, 1, rand_file);
    fclose(rand_file);
}

/*
 * Esta funcion deshabilita la salida de texto en la
 * terminal, para evitar que los passwords salgan
 * impresos en pantalla
 *
 * @author Cristobal Liendo
 * @return void
*/

struct termios original_f, modified_f;

void disable_output() {
    tcgetattr(fileno(stdin), &original_f);

    modified_f = original_f;
    modified_f.c_lflag &= ~ECHO;
    modified_f.c_lflag |= ECHONL;

    tcsetattr(fileno(stdin), TCSANOW, &modified_f);
}

/*
 * Esta funcion habilta la salida de texto en pantalla,
 * regresa a las opciones originales de termios.
 *
 * @author Cristobal Liendo
 * @return void
*/

void enable_output() {
    tcsetattr(fileno(stdin), TCSANOW, &original_f);
}

/*
 * Esta funcion deshabilita el modo canonico en la terminal,
 * con el fin de evitar que se tenga que presionar enter
 * en la pantalla principal. 
 * 
 * Precaucion: esta funcion no puede ser usada entre
 * disable_output() y enable_output() debido a que rescribiria
 * la configuracion por "default" de la terminal
 *
 * @author Cristobal Liendo
 * @return void
*/

void disable_canonical() {
    setbuf(stdout, NULL);
    tcgetattr(STDIN_FILENO, &original_f);

    modified_f = original_f;
    modified_f.c_lflag &= ~(ICANON|ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &modified_f);
}

/*
 * Esta funcion habilita el modo canonico en la terminal,
 * para regresar al funcionamiento "normal" de esta
 *
 * @author cristobal Liendo
 * @return void
*/

void enable_canonical() {
    tcgetattr(STDIN_FILENO, &original_f);

    original_f.c_lflag |= (ICANON|ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &original_f);
}

/*
 * Esta funcion creau un usuario de tipo "type" y regresa
 * el indice de la posicion en la que se encuentra el usuario 
 * dentro del arreglo de usuarios
 *
 * @author Cristobal Liendo
 * @param *usuarios    es el apuntador a una estructura de tipo
 *                     ManejoUsuarios
 * @param type         es un entero que indica el tipo de usuario.
 *                     por el momento los dos tipos de usuarios que
 *                     pueden haber es ADMIN y MORTAL definidos en
 *                     aleer.c
 * @return int
*/

int add_user(ManejoUsuarios *usuarios, int type) {
    int index = usuarios->actual;
    int success = 0;

    unsigned char password[256], salt[128], hash[256];
    unsigned char msg[200], a_credito[10];

    char nombre[100], direccion[100], email[100];
    int fecha_nac[3];

    float credito;

    while (!success) {
        // suponemos que el correo es unico
        success = 1;

        menu_agregar_usuario(
            nombre,
            password,
            fecha_nac,
            direccion,
            email,
            a_credito
        );

        for (int i = 0; i < usuarios->actual; i++) {
            // Se encontro un usuario
            if (strcmp(usuarios->usuarios[i].email, email) == 0)
                success = 0;
        }

        if (!success)
            printf("\tYa existe un usuario registrado con el mismo correo electronico\n");
    }

    strcpy(usuarios->usuarios[index].nombre, nombre);
    strcpy(usuarios->usuarios[index].direccion, direccion);
    strcpy(usuarios->usuarios[index].email, email);

    usuarios->usuarios[index].activo = 1;

    usuarios->usuarios[index].tipo_usuario = type;
    usuarios->usuarios[index].disponibles = 3;
    usuarios->usuarios[index].id = index;

    // se deberia llevar una bitacora de transacciones
    usuarios->usuarios[index].credito = credito;

    sprintf(msg, "Adición de crédito %.3f de usuario: %s", credito,  usuarios->usuarios[index].nombre);
    log_msg(msg);
    
    // genera el salt del credito
    generate_salt(128, salt);
    memcpy(usuarios->usuarios[index].c_salt, salt, 128);

    // genera el hash del credito actual
    sprintf(a_credito, "%f", credito);
    fastpbkdf2_hmac_sha256(a_credito, strlen(a_credito), salt,
        128, 4096, hash, 256);

    memcpy(usuarios->usuarios[index].c_hash, hash, 256);

    generate_salt(128, salt);
    memcpy(usuarios->usuarios[index].salt, salt, 128);

    fastpbkdf2_hmac_sha256(password, strlen(password), salt,
        128, 4096, hash, 256);

    memcpy(usuarios->usuarios[index].contrasena, hash, 256);

    for (int i = 0; i < 3; i++)
        usuarios->usuarios[index].fecha_nacimiento[i] = fecha_nac[i];

    usuarios->actual++;

    if (type == ADMIN)
        sprintf(msg, "Creacion de administrador %s", email);
    else
        sprintf(msg, "Creacion de usuario %s", email);

    log_msg(msg);

    FILE *usuarios_db;

    usuarios_db = fopen("usuarios.dat", "w");
    fwrite(usuarios, sizeof(*usuarios), 1, usuarios_db);
    fclose(usuarios_db);

    return index;
}

/*
 * Esta funcion determina si el usuario es mayor de edad o no
 * regresa verdadero si lo es, y falso si no lo es
 *
 * @author Cristobal Liendo, Guillermo Ortega
 * @param *usuario      un apuntador al usuario que se esta checando la edad
 * @return int
*/

int legal(Usuario *usuario) {
    struct tm dob;
    time_t now, dob2;

    dob.tm_sec = 0;
    dob.tm_year = usuario->fecha_nacimiento[2] - 1900;
    dob.tm_mon = usuario->fecha_nacimiento[1] - 1;
    dob.tm_mday = usuario->fecha_nacimiento[0];
    dob.tm_hour = 0;
    dob.tm_min = 0;
    dob.tm_sec = 0; 
    dob.tm_isdst = -1;

    dob2 = mktime(&dob);

    time(&now);

    return (difftime(now, dob2) >= 60*60*24*365*18);
}
