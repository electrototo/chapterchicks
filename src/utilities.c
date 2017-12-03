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
        success = menu_agregar_usuario(
            nombre,
            password,
            fecha_nac,
            direccion,
            email,
            a_credito
        );

        if (success == -1)
            return -1;

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

    sscanf(a_credito, "%f", &credito);

    // se deberia llevar una bitacora de transacciones
    usuarios->usuarios[index].credito = credito;

    sprintf(msg, "Adición de crédito %.2f de usuario: %s", credito,  usuarios->usuarios[index].nombre);
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

int legal(int *fecha_nacimiento) {
    struct tm dob;
    time_t now, dob2;

    dob.tm_sec = 0;
    dob.tm_year = fecha_nacimiento[2] - 1900;
    dob.tm_mon = fecha_nacimiento[1] - 1;
    dob.tm_mday = fecha_nacimiento[0];
    dob.tm_hour = 0;
    dob.tm_min = 0;
    dob.tm_sec = 0; 
    dob.tm_isdst = -1;

    dob2 = mktime(&dob);

    time(&now);

    return (difftime(now, dob2) >= 60*60*24*365*18);
}

/*
 * Esta funcion sirve para guardar los datos de @p struct en la base
 * de datos @p name, de tamaño @p size
 *
 * @author Cristobal Liendo
 * @param structure    Los datos a guardar
 * @param size         Tamaño en bytes de @p structure
 * @param *name        Nombre de la base de datos
*/

void save_db(void *structure, unsigned int size, char *name) {
    FILE *db;

    db = fopen(name, "w");
    fwrite(structure, size, 1, db);
    fclose(db);
}

/*
 * Esta funcion sirve para validar los datos que el usuario haya ingresado,
 * se va a usar en las funciones de menus
 *
 * @author Cristobal Liendo
 * @param message  El mensaje que se le va a mostrar al usuario
 * @param start    El inicio del rango valido
 * @param end      El final del rango valido
 * @return int
*/

int validate_answer(char *message, int start, int end) {
    int input;

    do {
        printf("%s", message);
        scanf("%d", &input);
        getchar();
    } while(input < start || input > end);

    return input;
}

/* 
 * Esta funcion sirve para agregar un libro a la renta del usuario,
 * regresa un 1 si fue exitoso, 2 si no alcanzó el dinero o 3 si
 * no existe el libro, 4 si el usuario ya no puede rentar mas libros
 *
 * @author Cristobal Liendo
 * @param *user   El usuario que se encuentra registrado
 * @param *bib    La biblioteca donde se encuentran los libros  
 * @return int
*/

int add_book(Usuario *user, Biblioteca *bib, ManejoAutor *autores,
        ManejoCategoria *categorias, ManejoPrestamo *prestamos) {
    char name[100], msg[100];

    unsigned char salt[128], hash[256], a_credito[10];

    Libro *libro;

    int eleccion = menu_rentar_libro(name);

    int success = 3;
    for (int i = 0; i < bib->actual; i++) {
        if (eleccion == 1) {
            if (strcmp(name, bib->libros[i].titulo) == 0) {
                libro = &bib->libros[i];
                success = 1;

                break;
            }
        }
        else if (eleccion == 2) {
            if (strcmp(name, bib->libros[i].ISBN10) == 0) {
                libro = &bib->libros[i];
                success = 1;

                break;
            }
        }
        else if (eleccion == 3) {
            if (strcmp(name, bib->libros[i].ISBN13) == 0) {
                libro = &bib->libros[i];
                success = 1;

                break;
            }
        }
    }

    // si se encontro el libro
    if (success == 1) {
        // comprueba que el usuario tenga el dinero suficiente
        if (user->credito < libro->costo)
            success = 2;
        else if (user->disponibles == 0)
            success = 4;
        else {
            // recalcula el dinero del usuario
            user->credito = user->credito - libro->costo;

            // tambien el hash del credito
            sprintf(a_credito, "%f", user->credito);
            fastpbkdf2_hmac_sha256(a_credito, strlen(a_credito), user->c_salt,
                128, 4096, hash, 256);

            memcpy(user->c_hash, hash, 256);

            // aumenta la cantidad de veces que se ha prestado el libro
            libro->prestamos++;

            // aumenta la cantidad de veces que el autor ha sido prestado
            for (int i = 0; i < autores->actual; i++) {
                if (libro->autor == autores->autores[i].id) {
                    autores->autores[i].prestados++;

                    break;
                }
                else {
                    sprintf(msg, "Error inesperado al buscar el autor");
                    log_msg(msg);
                }
            }

            // aumenta la cantidad de veces que el genero ha sido prestado
            for (int i = 0; i < categorias->actual; i++) {
                if (libro->categoria == categorias->categorias[i].id) {
                    categorias->categorias[i].prestados++;

                    break;
                }
                else {
                    sprintf(msg, "Error inesperado al buscar la categoria");
                    log_msg(msg);
                }
            }

            // agrega el libro a los libros del usuario
            user->libros[3 - user->disponibles] = libro->id;

            // disminuye la cantidad de libros que puede prestar
            user->disponibles--;

            // crea un registro
            prestamos->prestamos[prestamos->actual].libro = libro->id;
            prestamos->prestamos[prestamos->actual].usuario = user->id;
            prestamos->prestamos[prestamos->actual].fecha_prestamo = time(NULL);
            prestamos->prestamos[prestamos->actual].fecha_devolucion = time(NULL) + (60 * 60 * 24 * 30);

            prestamos->actual++;

            // guarda un mensaje informativo
            sprintf(msg, "El usuario %s rento el libro %s", user->nombre, libro->titulo);
            log_msg(msg);

            // guarda todos los cambios en las bases de datos
            save_db(bib, sizeof(*bib), "biblioteca.dat");
            save_db(autores, sizeof(*autores), "autores.dat");
            save_db(categorias, sizeof(*categorias), "categorias.dat");
            save_db(prestamos, sizeof(*prestamos), "prestamos.dat");
        }
    }

    return success;
}

/* 
 * Esta funcion busca en la biblioteca de libros el libro
 * que tenga el mismo id y lo regresa
 *
 * @author Cristobal Liendo
 * @param id    el id del libro a buscar
 * @param *bib  la biblioteca donde se guardan los libros
 * @return Libro
*/
Libro find_book_by_id(int id, Biblioteca *bib) {
    for (int i = 0; i < bib->actual; i++) {
        if (bib->libros[i].id == id)
            return bib->libros[i];
    }
}

/*
 * Esta funcion busca en los usuarios el usuario que tenga el
 * mismo id y lo regresa
 *
 * @author Cristobal Liendo
 * @param id     el id del usuario a buscar
 * @param *users donde se encuentran los usuarios
 * @return Usuario
*/
Usuario find_user_by_id(int id, ManejoUsuarios *users) {
    for (int i = 0; i < users->actual; i++) {
        if (users->usuarios[i].id == id)
            return users->usuarios[i];
    }
}
