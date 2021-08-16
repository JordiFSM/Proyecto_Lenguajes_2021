<<<<<<< HEAD
#include <stdio.h>

void menuPrincipal(){
	int opcion = 0;
	printf("\t*******Sistema de administracion de aulas*******\n\t\t\tMenu Principal");
	printf("\n\t(Debe ingresar un numero valido en el menu)\n\t1. Opciones Operativas\n\t2. Opciones Administrativas\n\t3. Salir\n\tIndique a que opcion desean ingresar: ");
	scanf("%i",&opcion);
	if (opcion = 1){
		menuOperativo();
	}
}

void menuOperativo(){
	int opcion = 0;
	printf("\n\n\t*******Sistema de administracion de aulas*******\n\t\t  Menu de Opciones Operativas");
	printf("\n\t(Debe ingresar un numero valido en el menu)\n\t1. Informacion de Aulas\n\t2. Informacion de Profesores\n\t3. Informacion de Cursos\n\t4. Informacion de Cursos por Periodo\n\t5. Reservacion de Aulas\n\t6. Cancelar reservacion de Aulas\n\t7. Estadisticas\n\t8. Salir\n\tIndique a que opcion desean ingresar: ");
	scanf("%i",&opcion);
}

int main(){
	menuPrincipal();
=======
#include<stdio.h>
int main(){
	printf("Hola Mundo");
>>>>>>> 343a1d95ead6d3e85371abff4d916c3f6e308c29
	return 0;
}