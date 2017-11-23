#include <stdio.h>
#include <menus.h>
#include <utilities.h>

int main() {
    char usuario[50], pwd[50], direccion[50];
    char correo[254], password1[50], password2[50];
    char nombre_libro [100],nombre_autor[50],categoria[50];
    char isbn[14];

    int fecha[3], opcion_principal, opcion_acceso_admin, opcion_admin;
    float *costo_libro;

    creditos();
    
    menu_principal();

    if (opcion_principal==1) {
        menu_acceso(correo, password1);
    }

    else {
        menu_agregar_usuario (usuario, pwd, fecha, direccion);
    }

    printf("Bienvenido de vuelta, %s.\n", usuario);
    
    
    
    //aqui debería hacerse una validación para ver
    //si el usuario es admin o no, por el momento lo dejaré así
    int sino;
    printf("¿Eres admin? Nota*: Esta validación se realiza de manera automática\n[1]Si\n[2]No\n");
    scanf("%d", &sino);
    
    
    
    if (sino==1){

      menu_administrador_como ();
      
      if(opcion_acceso_admin == 1)
	{	  
	  menu_administrador_general();
	  
	  if (opcion_admin == 1){
	    printf("\nInforme de libros en préstamo\n");
	  }
	  
	  else if (opcion_admin==2){
	    printf("\nInforme de usuarios y libros en préstamo\n");
	  }
	  
	  else if (opcion_admin==3){
	    menu_registrar_libro (nombre_libro,nombre_autor,categoria,isbn, costo_libro);
	  } 
	  
	  else if (opcion_admin==4){
	    printf("\nDar de baja a un usuario\n");
	    printf("Usuario: \n");
	  }
	  
	  else if (opcion_admin==5){
	    printf("\nCategoría mas popular: ");
	    printf("\nAutor mas popular: ");
	    printf("\nTítulo mas popular: ");
	  }
	  
	  else if (opcion_admin==6){
	    printf("\nAyuda\n");
	  }
	  
	  else if (opcion_admin>=7){
	    return 0;
	  }
	}
    }
    
    else if (opcion_acceso_admin ==2){
      menu_usuario ();
    }
    
    //creditos();
    
    return 0;    
    
}    
