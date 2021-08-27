
#include <stdio.h>
#include <mysql.h> 
#include <string.h> 
#include "BD.c"

void menuPrincipal(){
	int opcion = opcion = (int)malloc(sizeof(int));
	conectarBaseDatos();
	do{
		printf("\t****Sistema de administracion de aulas**\n\t\t\tMenu Principal");
		printf("\n\t(Debe ingresar un numero valido en el menu)\n\t1. Opciones Operativas\n\t2. Opciones Administrativas\n\t3. Salir\n\tIndique a que opcion desean ingresar: ");
		scanf("%d",&opcion);
		while(getchar()!='\n');
		if (opcion == 1){
			menuOperativo();
		}
	}while(opcion != 0);
}

void menuOperativo(){
	int opcion = 0;
	printf("\n\n\t****Sistema de administracion de aulas**\n\t\t  Menu de Opciones Operativas");
	printf("\n\t(Debe ingresar un numero valido en el menu)\n\t1. Informacion de Aulas\n\t2. Informacion de Profesores\n\t3. Informacion de Cursos\n\t4. Informacion de Cursos por Periodo\n\t5. Reservacion de Aulas\n\t6. Cancelar reservacion de Aulas\n\t7. Estadisticas\n\t8. Salir\n\tIndique a que opcion desean ingresar: ");
	scanf("%i",&opcion);
	while(getchar()!='\n');
    if (opcion == 2){
        menuProfesor();
    }else if(opcion == 3){
		listarCursos();
	}else if(opcion == 4){
		menuCursoPeriodo();
	}else if (opcion == 1){
		agregarAulas();
	}else if (opcion == 5){
		reservarAulas();
	}else if(opcion == 6){
		cancelarReservacion();
	}
}

void menuProfesor(){
    int opcion = 0;
    printf("\n\n\t****Sistema de administracion de aulas**\n\t\t  Menu de Opciones de Profesores");
    printf("\n\t(Debe ingresar un numero valido en el menu)\n\t1. Incluir Profesor\n\t2. Mostrar Informacion de Profesores\n\t3. Borrar todos los Profesores\n\t4.Volver\n\tIndique a que opcion desean ingresar: ");
    scanf("%i",&opcion);
	while(getchar()!='\n');
    if (opcion == 2){
        mostrarProfesores();
    }else if(opcion == 1){
		incluirProfesor();
	}else if(opcion == 3){
		borrarTodo();
	}else if (opcion == 4){
		menuOperativo();
	}else{
		printf("La Opcion indicada es invalida");
		menuProfesor();
	}
}

void menuCursoPeriodo(){
    int opcion = 0;
    printf("\n\n\t****Sistema de administracion de aulas**\n\t\t  Menu de Opciones de Cursos por Periodo");
    printf("\n\t(Debe ingresar un numero valido en el menu)\n\t1. Incluir Curso\n\t2. Mostrar Informacion de Cursos\n\t3. Borrar Curso\n\t4.Volver\n\tIndique a que opcion desean ingresar: ");
    scanf("%i",&opcion);
	while(getchar()!='\n');
    if (opcion == 2){
        listarCursosPeriodo();
    }else if(opcion == 1){
		incluirCursos();
	}else if(opcion == 3){
		borrarCursoPeriodo();
	}else if(opcion==4){
		menuOperativo();
	}else{
		printf("La Opcion indicada es invalida");
		menuCursoPeriodo();
	}
}

int main(){
	menuPrincipal();
}