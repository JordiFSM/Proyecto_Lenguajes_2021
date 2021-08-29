#include "BD.c"

/*****keys administrativos************************
 * Nombre del archivo: main.c
 * Tipo de archivo: codigo fuente c
 * Proyecto: PP1_LENGUAJES keys
 * Autor: Jordi Segura Madrigal, Kevin Lanzas Quen
 * Empresa: Instituto Tecnológico de Costa Rica
 *****Descripción**********************************
 * Archivo que contiene los menus del programa, es el encargado de 
 * interactuar con el usuario y realizar las ordenes indicadas, así como mostrar
 * los datos que se pidan desde la consola.
 *****Versión**************************************
 * ## 1.0 | Fecha: 28/08/2021 | Autor: Jordi Segura Madrigal, Kevin Lanzas Quen
 * 
 **************************************************/

/*****Nombre***************************************
 * menuPrincipal
 *****Descripción**********************************
 * Funcion encargada de mostrar las opciones del menu
 * principal lo cual desplieaga los menus de opciones
 * operativas y administrativas, ademas de salir.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

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
		}else if(opcion ==2){
			menuAdministrativo();
		}else if(opcion == 3){
			break;
		}
	}while(opcion != 0);
}

/*****Nombre***************************************
 * menuOperativo
 *****Descripción**********************************
 * Funcion encargada de mostrar las opciones del menu
 * Operativo lo cual desplieaga el menus de opciones y
 * envia al usuario donde desee ir.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

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
	}else if (opcion == 7){
		menuEstadisticas();
	}else if (opcion == 8){
		return;
	}
}

/*****Nombre***************************************
 * menuAdministrativo
 *****Descripción**********************************
 * Funcion encargada de mostrar las opciones del menu
 * Administrativo lo cual desplieaga el menus de opciones y
 * envia al usuario donde desee ir.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void menuAdministrativo(){
	int opcion = 0;
	printf("\n\n\t****Sistema de administracion de aulas**\n\t\t  Menu de Opciones Administrativas");
	printf("\n\t(Debe ingresar un numero valido en el menu)\n\t1. Consultar por dia\n\t2. Consultar por aula\n\t3. Consultar por Curso\n\t4. Salir\n\tIndique a que opcion desean ingresar: ");
	scanf("%i",&opcion);
	while(getchar()!='\n');
    if (opcion == 1){
        consultaFecha();
    }else if(opcion == 2){
		consultaAula();
	}else if(opcion == 3){
		consultaCurso();
	}else{
		menuPrincipal();
	}
}

/*****Nombre***************************************
 * menuAdministrativo
 *****Descripción**********************************
 * Funcion encargada de mostrar las opciones del menu
 * de profesores lo cual desplieaga el menus de opciones y
 * envia al usuario donde desee ir.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

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

/*****Nombre***************************************
 * menuCursoPeriodo
 *****Descripción**********************************
 * Funcion encargada de mostrar las opciones del menu
 * de cursos por periodo lo cual desplieaga el menus de opciones y
 * envia al usuario donde desee ir.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

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

/*****Nombre***************************************
 * menuEstadisticas
 *****Descripción**********************************
 * Funcion encargada de mostrar las opciones del menu
 * de estadisticaslo cual desplieaga el menus de opciones y
 * envia al usuario donde desee ir.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void menuEstadisticas(){
    int opcion = 0;
    printf("\n\n\t****Sistema de administracion de aulas**\n\t\t  Menu de Opciones de estadisticas");
    printf("\n\t(Debe ingresar un numero valido en el menu)\n\t1. Aulas mas reservadas\n\t2. Profesores mas reservados\n\t3. Cantidad de reservaciones anio-mes\n\t4.Volver\n\tIndique a que opcion desean ingresar: ");
    scanf("%i",&opcion);
	while(getchar()!='\n');
    if (opcion == 1){
        mostrarAulasMasReservadas();
    }else if(opcion == 2){
		mostrarProfesoresMasReservados();
	}else if(opcion == 3){
		mostrarReservasAnioMes();
	}else if (opcion == 4){
		menuOperativo();
	}else{
		printf("La Opcion indicada es invalida");
		menuProfesor();
	}
}

int main(){
	menuPrincipal();
}
