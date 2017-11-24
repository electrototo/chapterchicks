#include <stdio.h>
#include <menus.h>
#include <utilities.h>

int main() 
{
    char usuario[50], pwd[50], direccion[50];
    char correo[254], password1[50], password2[50];
    char nombre_libro [100],nombre_autor[50],categoria[50];
    char isbn[14];

    int fecha[3], opcion_principal, opcion_acceso_admin, opcion_admin, total_libros_prestamo;
    float *costo_libro;

    creditos();
    
    opcion_principal = menu_principal();

    if (opcion_principal == 1) {
        menu_acceso(correo, password1);
    }

    else {
      menu_agregar_usuario(usuario, pwd, fecha, direccion, email);
    }

    //solo deberia imprimirse esto si el usuario
    //ya tiene cuenta
    printf("Bienvenido de vuelta, %s.\n", usuario);
    
    //aqui debería hacerse una validación para ver
    //si el usuario es admin o no, por el momento lo dejaré así
    int sino;
    printf("¿Eres admin? Nota*: Esta validación se realiza de manera automática\n[1]Si\n[2]No\n");
    scanf("%d", &sino);
    getchar();
    
    
    if (sino == 1){
        opcion_acceso_admin = menu_administrador_como();
    
        if(opcion_acceso_admin == 1) {
            opcion_admin = menu_administrador_general();
        
            switch (opcion_admin) {
                
                case 1: 
		  menu_informe_prestamos ();
                    break;
                    
                case 2:
                    printf("\nInforme de usuarios y libros en préstamo\n");
                    break;
                    
                case 3:
                    menu_registrar_libro (nombre_libro,nombre_autor,categoria,isbn, costo_libro);
                    break;
                    
                case 4:
                    printf("\nDar de baja a un usuario\n");
                    printf("Usuario: \n");
                    break;
                    
                case 5:
                    printf("\nCategoría mas popular: ");
                    printf("\nAutor mas popular: ");
                    printf("\nTítulo mas popular: ");
                    break;
                    
                case 6:
                    printf("\nAyuda\n");
                    break;
                    
                case 7:
                    return 0;
                    break;

                default:
                    break;
            }
        }
        else if (opcion_acceso_admin == 2){
            menu_usuario();
        }
    }

    else if (sino == 2){
        menu_usuario ();
    }

    return 0;    
    
}    
