
#include <stdio.h>
#include <menus.h>
#include <utilities.h>

int main() {
    char usuario[50], pwd[50], direccion[50];
    char email[254], password1[50], password2[50];
    char nombre_libro [100],nombre_autor[50],categoria[50];
    char isbn[14];

    int fecha[3], opcion_principal, opcion_acceso_admin, opcion_admin, total_libros_prestamo, opcion_ayuda;
    float *costo_libro;

    creditos();
    
    opcion_principal = menu_principal();

    if (opcion_principal == 1)
        menu_acceso(email, password1);

    else
        menu_agregar_usuario(usuario, pwd, fecha, direccion, email);


    printf("Bienvenid@ Elena.\n");
    
    //aqui debería hacerse una validación para ver
    //si el usuario es admin o no, por el momento lo dejaré así
    int sino;
    printf("¿Eres admin? Nota*: Esta validación se realiza de manera automática\n[1]Si\n[2]No\n");
    scanf("%d", &sino);
    getchar();
    
    int alta_o_baja;
    
    if (sino == 1){
        opcion_acceso_admin = menu_administrador_como();
        
        do{    
            if(opcion_acceso_admin == 1) {
                opcion_admin = menu_administrador_general();
      
                switch (opcion_admin) {
                    case 1: 
                        menu_informe_prestamos();
                        getchar();
                        break;
            
                    case 2:
                        menu_informe_usuarios();
                        getchar();
                        break;
            
                    case 3:
                        printf("¿Quieres dar de alta ó dar de baja un libro?\n[1]Alta\n[2]Baja\n");
                        scanf("%d", &alta_o_baja);
                        
                        if (alta_o_baja == 1){
                            menu_registrar_libro(nombre_libro,nombre_autor,categoria,isbn, costo_libro);
                        }

                        else {
                            printf("LIBRO #1\n");
                            printf("Título: Harry Potter y la Piedra Filosofal\n");
                            printf("Autor: J. K. Rowling\n");
                            printf("Categoría: Fantasía\n\n");
                            printf("LIBRO #2\n");
                            printf("Título: El Señor de los Anillos\n");
                            printf("Autor: J. R. R. Tolkien\n");
                            printf("Categoría: Fantasía\n");
                            printf("\n");
                            printf("¿Qué libro quieres dar de baja?\n");
                            printf("Opción: 1");
                            getchar();
                        }

                        getchar();
                        break;

                    case 4:
                        menu_baja_de_usuario();
                        getchar();
                        break;
                    
                    case 5:
                        menu_popular();
                        getchar();
                        break;
                        
                    case 6:
                        menu_ayuda();
                        break;
                    
                    case 7:
                        return 0;
                        break;
                
                    default:
                        break;
                }
            }
        } while (opcion_admin != 7);

        if (opcion_acceso_admin == 2){
            opcion_admin=menu_usuario();
        }
    }
    
    else if (sino == 2){
        menu_usuario ();
    }
    
    return 0;    
}
