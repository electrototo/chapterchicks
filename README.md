# chapterchicks
Proyecto final de fundamentos a la programación: simulación de renta de libros, programado en C.

## Descripción del proyecto
Es un sistema de subscripción en _línea_ (porque realmente no lo es) para libros libros que permite la administración de libros / clientes; vaya, como un netflix de libros, aka scribd.

Existen dos tipos de usuarios:
1. El _administrador del sistema_: es el encargado de administrar los libros y a los clientes subscriptos
2. El _cliente del servicio_: es aquel que renta y puede buscar libros.

## Compilación del proyecto
Por el momento se tiene un archivo makefile demasiado rudimental por lo que para poder compilar el archivo principal (que todava no existe) o cualquier otro archivo que haga uso de
las librerías, se tienen que seguir los siguientes pasos:
1. Crear una carpeta con nombre _obj_ dentro de _src_
2. Ejecutar `make name=nombre_del_archivo` donde *nombre_del_archivo* es el nombre del archivo **fuente** a compilar; aquel que hace uso de las librerías que se encuentran
dentro del repositorio

## Ejecución de _aleer_
Hay dos formas de ejecución del programa, la primera no tiene argumentos por lo que se ejecuta de la siguiente manera:

`$ aleer`

La segunda manera de ejecutar el programa es ingresando los siguientes argumentos:

| **Modificador** | **Comportamiento**                                                                             |
| --------------- | ---------------------------------------------------------------------------------------------- |
| -h              | Despliega el menú de ayuda al usuario                                                          |
| -c              | Despliega un informe de libros en préstamo                                                     |
| -usu            | Despliega el listado de todos los *usuaios del servicio* catalogados y muestra su alta y baja. |
| -a              | Indica al programa que se quiere crear una cuenta de administrador.                            |

## TODO
Por el momento el proyecto se encuentra en una etapa muy temprana. Cualquier duda y comentario será muy bienvenida dentro de la sección de issues. 
