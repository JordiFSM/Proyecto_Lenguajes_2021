#include <stdio.h>
#include <mysql.h> 
#include <string.h>

/*****keys administrativos************************
 * Nombre del archivo: BD.c
 * Tipo de archivo: codigo fuente c
 * Proyecto: PP1_LENGUAJES keys
 * Autor: Jordi Segura Madrigal, Kevin Lanzas Quen
 * Empresa: Instituto Tecnológico de Costa Rica
 *****Descripción**********************************
 * Estructura que contiene las funciones responsables de conectarse
 * a mysql, la base de datos del proyecto y realizar las diferentes consultas necesarias para 
 * el funcionamiento del sistema
 *****Versión**************************************
 * ## 1.0 | Fecha: 28/08/2021 | Autor: Jordi Segura Madrigal, Kevin Lanzas Quen
 * 
 **************************************************/

/* libreria que nos permite hacer el uso de las conexiones y consultas con MySQL */
MYSQL *conn; /* variable de conexión para MySQL */
MYSQL_RES *res; /* variable que contendra el resultado de la consuta */
MYSQL_ROW row; /* variable que contendra los campos por cada registro consultado */

char *server = "localhost"; /*direccion del servidor 127.0.0.1, localhost o direccion ip */
char *user = "root"; /*usuario para consultar la base de datos */
char *password = "Uzumakii2011"; /* contraseña para el usuario en cuestion */
char *database = "Sistema_Administracion_Aulas"; /*nombre de la base de datos a consultar */

/*****Nombre***************************************
 * conectarBaseDatos
 *****Descripción**********************************
 * Funcion responsable de tomar las variables globales
 * para lograr conectarse a la base de datos de mysql
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void conectarBaseDatos(){
	conn = mysql_init(NULL); /*inicializacion a nula la conexión */
	/* conectar a la base de datos */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{ /* definir los parámetros de la conexión antes establecidos */
		fprintf(stderr, "%s\n", mysql_error(conn)); /* si hay un error definir cual fue dicho error */
		exit(1);
	}
}

/*****Nombre***************************************
 * desconectarBaseDatos
 *****Descripción**********************************
 * Funcion responsable de lograr desconectarse de la
 * base de datos de mysql
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void desconectarBaseDatos(){
		/* se libera la variable res y se cierra la conexión */
	mysql_free_result(res);
	mysql_close(conn);
}

/*****Nombre***************************************
 * mostrarProfesores
 *****Descripción**********************************
 * Funcion que realiza la consulta de seleccionar los 
 * profesores dentro de la base de datos y los muestra todos.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void mostrarProfesores(){
	/* enviar consulta SQL */
	if (mysql_query(conn, "select * from Profesores"))
	{ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("\tNombre\t\tCedula\n");
	while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
		printf("\t%s\t%s\n", row[0],row[1]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
	
	menuOperativo();
}

/*****Nombre***************************************
 * incluirProfesor
 *****Descripción**********************************
 * Funcion que realiza el query de insercion a la tabla de
 * profesores con los datos que pide en las entradas, para 
 * al final insertar el profesor a la base de datos.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void incluirProfesor(){
	char nombre [30];
	int cedula;
	char query[200]= {0};
	printf("\tDigite la cedula del profesor: ");
	scanf("%d", &cedula);
	while(getchar()!='\n');

	printf("\tDigite el nombre del profesor: \n");
	//scanf("%s", &nombre);
	fgets(nombre,30,stdin);
	nombre[strlen(nombre)-1] = '\0';
	/* enviar consulta SQL */
	snprintf(query,128,"INSERT INTO Profesores(Nombre,Cedula_Profesor) VALUES (\'%s\',\'%d\')", nombre, cedula);
	/* definicion de la consulta y el origen de la conexion */
	if(mysql_query(conn, query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
        menuOperativo();
		//exit(1);
	}
	printf("\tEl profesor fue incluido con exito!!!");
	menuOperativo();
}

/*****Nombre***************************************
 * borrarTodo
 *****Descripción**********************************
 * Funcion que realiza el query de Delete a la tabla,
 * y borra todos los registros de profesores dentro de 
 * la base de datos.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void borrarTodo(){
	if (mysql_query(conn, "DELETE from Profesores"))
	{ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	printf("\tLos profesores fueron borrados con exito!!!");
}

/*****Nombre***************************************
 * listarCursos
 *****Descripción**********************************
 * Funcion que realiza el query de consulta Select a 
 * todos los registros de Cursos que hayan en la base de datos
 * para luego hacer impresión de estos en consola.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void listarCursos(){
	/* enviar consulta SQL */
	mysql_query(conn, "select * from Cursos");
	res = mysql_use_result(conn);
	printf("\tNombre\t\tCodigo_Curso\tCodigo_Carrera\n");
	while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
		printf("\t%s\t%s\t%s\n", row[0],row[1],row[2]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
	menuOperativo();
}

/*****Nombre***************************************
 * incluirCursos
 *****Descripción**********************************
 * Funcion que pide los datos necesarios por medio de entradas
 * en la consola para realizar la insercion de un curso por
 * periodo a la base de datos de mysql.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void incluirCursos(){
	int codigoCurso;
	int year; 
    int periodo;
    int grupo;
    int cedulaProfe;
    int cantEstudiante;
	char query[500]= {0};
	printf("\tDigite el codigo del curso: ");
	scanf("%d", &codigoCurso);
	while(getchar()!='\n');
	printf("\tDigite el anio: ");
	scanf("%d", &year);
	while(getchar()!='\n');
    if(year > 2035 || year < 2021){
        printf("\tEL anio debe ser mayor o igual a 2021 o menor a 2035");
        incluirCursos();
    }
    printf("\tDigite el periodo: ");
	scanf("%d", &periodo);
	while(getchar()!='\n');
    if(periodo == 1 || periodo == 2){
        printf("\tDigite el grupo: ");
	    scanf("%d", &grupo);
	    while(getchar()!='\n');
        printf("\tDigite la cedula del profesor: ");
	    scanf("%d", &cedulaProfe);
	    while(getchar()!='\n');
        printf("\tDigite la cantidad de estudiantes: ");
	    scanf("%d", &cantEstudiante);
	    while(getchar()!='\n');
    }else{
        printf("\tEl periodo indicado es invalido \n");
        incluirCursos();
    }
	/* enviar consulta SQL */
	snprintf(query,500,"INSERT INTO Cursos_por_Periodo(Codigo_Curso,Periodo,Anio,Grupo,Cedula_Profesor,Cantidad_Estudiantes) VALUES (\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\')", codigoCurso, periodo,year,grupo,cedulaProfe,cantEstudiante);
	/* definicion de la consulta y el origen de la conexion */
	if(mysql_query(conn, query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
        menuOperativo();
		//exit(1);
	}
	printf("\tEl curso fue agregado al periodo indicado");
	menuOperativo();
}

/*****Nombre***************************************
 * listarCursosPeriodo
 *****Descripción**********************************
 * Funcion encargada de hacer la solicitud de los cursos 
 * por periodo a la base de datos para luego mostrarlos
 * por impresión en consola.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void listarCursosPeriodo(){
	/* enviar consulta SQL */
	mysql_query(conn, "select * from Cursos_por_Periodo");
	res = mysql_use_result(conn);
	printf("\tCodigoCurso\tPeriodo\tAnio\tGrupo\tCedulaProfesor\tCantidadEstudiantes\n");
	while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
		printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", row[0],row[1],row[2],row[3],row[4],row[5]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
	menuOperativo();
}	

/*****Nombre***************************************
 * borrarCursoPeriodo
 *****Descripción**********************************
 * Funcion encargada de hacer la solicitud de los datos de 
 * un curso por periodo existente en la base de datos, por
 * medio de entradas por consola, realiza el query y 
 * elimina este registro de ella.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void borrarCursoPeriodo(){
	int codigoCurso;
	int year; 
    int periodo;
    int grupo;
	char query[500]= {0};
	printf("\tDigite el codigo del curso: ");
	scanf("%d", &codigoCurso);
	while(getchar()!='\n');
	printf("\tDigite el anio: ");
	scanf("%d", &year);
	while(getchar()!='\n');
	printf("\tDigite el periodo: ");
	scanf("%d", &periodo);
	while(getchar()!='\n');
	printf("\tDigite el grupo: ");
	scanf("%d", &grupo);
	while(getchar()!='\n');
	snprintf(query,500,"DELETE FROM Cursos_por_Periodo WHERE Codigo_Curso = \'%d\' AND Periodo = \'%d\' AND Anio = \'%d\' AND Grupo = \'%d\'", codigoCurso, periodo,year,grupo);
	if (mysql_query(conn, query)){ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		menuOperativo();
		//exit(1);
	}
	printf("\tEl curso fue eliminado del periodo indicado");
}

/*****Nombre***************************************
 * agregarAulas
 *****Descripción**********************************
 * Funcion encargada de abrir el archivo que contiene
 * la lista de las aulas, separarlas en tokens con su
 * nombre y su cantidad, agregarlas despues de valida 
 * el formato que se pide. En que haya alguna que no 
 * cumpla con el formato o ya esté dentro seguira revisando
 * los tokens hasta que termine de leer el archivo sin 
 * detenerse por ello.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/


void agregarAulas(){
	FILE *archivo;
	char buffer[500];
	char *aula;
	char query[500];
	char *canESt;
	int bandera = 0;
	int banderaError = 0;
	archivo = fopen("./Aulas.txt", "r");
	if(archivo == NULL) { 
		printf("\tNo se pudo abrir el archivo... \n"); 
		menuOperativo(); 
	}
	while (fgets(buffer,500, archivo)){
        // Aquí, justo ahora, tenemos ya la línea. Le vamos a remover el salto
        strtok(buffer, "\n");
		char *token = (char*)malloc(10);
    	token = strtok(buffer, ",");
    	if(token != NULL){
        	while(token != NULL){
            	// Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
				if (bandera == 0){
					aula = (char*)malloc(3);
					aula = token;
					if (strlen(aula) > 3){
						printf("Nombre del aula supera el limite de caracteres");
						banderaError =3;
						break;
					}else{
						printf("\tToken: %s\n", aula);
						if (isalpha(aula[0])){
							int cont = 1;
							int largo = strlen(aula)-1;
							while (cont <= largo){
								if(isdigit(aula[cont])){
									cont+=1;
								}else{
									printf("\tEl nombre del aula: %s no cumple el formato \n",aula);
									printf("\tSe seguiran insertando las aulas si el formato es correcto\n");
									break;
								}
							}
						}
						bandera += 1;
					}	
				}else if(bandera == 1){
					canESt = (char*)malloc(3);
					canESt = token;
					if (strlen(canESt) > 3){
						printf("\tLa cantidad de estudiantes excede la maxima capacidad del aula \n");
						banderaError= 3;
						break;
					}else{
						int cont = 0;
						int largo = strlen(canESt)-1;
						while (cont <= largo){
							if(isdigit(canESt[cont])){
								printf("\tSI");
								cont+=1;
							}else{
								printf("\tNO");
								printf("\tLa capacidad indicada %s no cumple la capacidad maxima del aula \n",canESt);
								printf("\tSe seguiran insertando las aulas si el formato es correcto\n");
								break;
							}
						}
					}
				}
           	 	//printf("Token: %s\n", token);
            	token = strtok(NULL, ",");
        	}
			bandera = 0;
			if(banderaError != 3){
				snprintf(query,500,"INSERT INTO Aulas(Nombre_Aula,Capacidad) VALUES (\'%s\',\'%d\')", aula, atoi(canESt));
				/* definicion de la consulta y el origen de la conexion */
				if(mysql_query(conn, query)){
					fprintf(stderr, "%s\n", mysql_error(conn));
        			//menuOperativo();
					//exit(1);
				}
			}
			banderaError = 0;	
		}

    }
	printf("\tSe agregaron las aulas que no estan repetidas y las que cumplen el formato");
	fclose(archivo);
}

/*****Nombre***************************************
 * reservarAulas
 *****Descripción**********************************
 * Funcion encargada de obtener los datos de la consola
 * para crear una reserva valida para ser ingresada en 
 * la base de datos, permite agregar más de un aula si 
 * la capacidad del aula es menor a la cantidad de estudiantes 
 * del curso.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void reservarAulas(){
	int codActual = maxReservaciones();
	mysql_free_result(res);
	int capacidadAula;
	int capacidadCurso;
	char query[1000]= {0};
	char query2[1000] = {0};
	int dia;
	int mes;
	int year;
	int horaInicio;
	int minutosInicio;
	int horaFin;
	int minutosFin;
	char nombreAula[3];
	int periodo;
	int codigoCurso;
	int grupo;

	printf("\tDigite el dia para la reservacion: ");
	scanf("%d",&dia);
	if (dia > 31 || dia < 0){
		printf("\tEl dia indicado es incorrecto \n");
		reservarAulas();
	}
	printf("\tDigite el mes para la reservacion\n: ");
	scanf("%d",&mes);
	if (mes > 12 || mes < 1){
		printf("\tEl mes indicado es incorrecto\n");
		reservarAulas();
	}
	printf("\tDigite el anio para la reservacion\n");
	scanf("%d",&year);
	if(year > 2035 || year < 2021){
		printf("\tEl anio indicado es invalido\n");
		reservarAulas();
	}
	printf("\tDigite la hora de inicio de la reservacion: ");
	scanf("%d",&horaInicio);
	if (horaInicio < 0 || horaInicio > 23){
		printf("\tHora de inicio indicada es invalida\n");
		reservarAulas();
	}
	printf("\tDigite los minutos para la reservacion: ");
	scanf("%d",&minutosInicio);
	if(minutosInicio < 0 || minutosInicio > 59){
		printf("\tLos minutos indicados son invalidos\n");
		reservarAulas();
	}
	printf("\tDigite la hora final de la reservacion: ");
	scanf("%d",&horaFin);
	if (horaFin < 0 || horaFin > 23){
		printf("\tLa hora indicada no es valida\n");
		reservarAulas();
	}
	printf("\tDigite los minutos finales para la reservacion: ");
	scanf("%d",&minutosFin);
	if(minutosFin < 0 || minutosFin > 59){
		printf("\tLos minutos indicados son invalidos\n");
		reservarAulas();
	}
	if(horaInicio >= horaFin){
		printf("\tLas horas indicadas son invalidas\n");
		reservarAulas();
	}
	printf("\tDigite el nombre del aula:");
	scanf("%s",&nombreAula);
	
	printf("\tDigite el periodo de reservacion: ");
	scanf("%d",&periodo);
	if (periodo < 0 || periodo > 2){
		printf("\tPeriodo indicado es invalido\n");
		reservarAulas();
	}

	printf("\tDigite el codigo del curso:");
	scanf("%d",&codigoCurso);

	printf("\tDigite el grupo del curso:");
	scanf("%d",&grupo);

	snprintf(query,1000,"SELECT Capacidad from Aulas WHERE Nombre_Aula = \'%s\'", nombreAula);
	if(mysql_query(conn,query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("\tAula no encontrada");
		reservarAulas();
	}
	res = mysql_use_result(conn);
	row = mysql_fetch_row(res);
	capacidadAula = atoi(row[0]);
	mysql_free_result(res);

	snprintf(query,1000,"SELECT Cantidad_Estudiantes from Cursos_por_Periodo WHERE Codigo_Curso = \'%d\' AND Periodo = \'%d\' AND Anio = \'%d\' AND Grupo = \'%d\'", codigoCurso, periodo,year,grupo);
	if(mysql_query(conn,query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("\tCurso no enconrado");
		reservarAulas();
	}
	res = mysql_use_result(conn);
	row = mysql_fetch_row(res);
	capacidadCurso = atoi(row[0]);
	mysql_free_result(res);

	if(capacidadAula >= capacidadCurso){
		snprintf(query,1000,"INSERT INTO Reservacion_de_Aulas(Codigo_Reservacion,Fecha,Hora_Inicio,Hora_Fin,Codigo_Curso,Periodo,Año,Grupo,Nombre_Aula) VALUES (NULL,\'%d/%d/%d\',\'%d:%d:00\',\'%d:%d:00\',\'%d\',\'%d\',\'%d\',\'%d\',\'%s\')",year,mes,dia,horaInicio,minutosInicio,horaFin,minutosFin,codigoCurso,periodo,year,grupo,nombreAula);
		/* definicion de la consulta y el origen de la conexion */
		if(mysql_query(conn, query)){
			fprintf(stderr, "%s\n", mysql_error(conn));
        	reservarAulas();
		}
		printf("\tEl codigo de su reservacion es: %d \n",codActual+1);
		codActual ++;
	}else{
		int cupos = capacidadCurso - capacidadAula;
		snprintf(query,1000,"INSERT INTO Reservacion_de_Aulas(Codigo_Reservacion,Fecha,Hora_Inicio,Hora_Fin,Codigo_Curso,Periodo,Año,Grupo,Nombre_Aula) VALUES (NULL,\'%d/%d/%d\',\'%d:%d:00\',\'%d:%d:00\',\'%d\',\'%d\',\'%d\',\'%d\',\'%s\')",year,mes,dia,horaInicio,minutosInicio,horaFin,minutosFin,codigoCurso,periodo,year,grupo,nombreAula);
		/* definicion de la consulta y el origen de la conexion */
		if(mysql_query(conn, query)){
			fprintf(stderr, "%s\n", mysql_error(conn));
        	reservarAulas();
		}
		printf("\tEl codigo de su reservacion es: %d \n",codActual+1);
		codActual ++;
		while(cupos > 0){
			char nombreAula[3];
			printf("\nSe necesita un aula mas porque la cantidad de estudiantes supera el limite del aula \n");
			printf("\tDigite el nombre del aula:");
			scanf("%s",&nombreAula);
			int capacidad;
			snprintf(query,1000,"SELECT Capacidad from Aulas WHERE Nombre_Aula = \'%s\'", nombreAula);
			if(mysql_query(conn,query)){
				fprintf(stderr, "%s\n", mysql_error(conn));
				printf("\tAula no encontrada \n");
			}else{
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);
				capacidad = atoi(row[0]);
				mysql_free_result(res);

				snprintf(query,1000,"INSERT INTO Reservacion_de_Aulas(Codigo_Reservacion,Fecha,Hora_Inicio,Hora_Fin,Codigo_Curso,Periodo,Año,Grupo,Nombre_Aula) VALUES (NULL,\'%d/%d/%d\',\'%d:%d:00\',\'%d:%d:00\',\'%d\',\'%d\',\'%d\',\'%d\',\'%s\')",year,mes,dia,horaInicio,minutosInicio,horaFin,minutosFin,codigoCurso,periodo,year,grupo,nombreAula);
				/* definicion de la consulta y el origen de la conexion */
				if(mysql_query(conn, query)){
					fprintf(stderr, "%s\n", mysql_error(conn));
				}else{
					cupos = cupos - capacidad;
					printf("\tEl codigo de su reservacion es: %d\n",codActual+1);
					codActual ++;
				}
				
			}
			
		}
		menuOperativo();
	}
}

/*****Nombre***************************************
 * maxReservaciones
 *****Descripción**********************************
 * Funcion encargada de obtener los datos de la consulta
 * del código máximo de las reservaciones.
 *****Retorno**************************************
 * int el numero siguiente de los códigos de reservacion
 *****Entradas*************************************
 * N/A
 **************************************************/

int maxReservaciones(){
	char query[500]= {0};
	snprintf(query,500,"SELECT MAX(Codigo_Reservacion) from Reservacion_de_Aulas");
	if(mysql_query(conn, query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		return 0;
	}else{
		res = mysql_use_result(conn);
		row = mysql_fetch_row(res);
		if(row[0] == NULL){
			return 0;
		}
		printf("%d",atoi(row[0]));
		return atoi(row[0]);
	}
}

/*****Nombre***************************************
 * cancelarReservacion
 *****Descripción**********************************
 * Funcion encargada de obtener los datos del identificador 
 * de reservación para ser eliminado en la base de datos.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void cancelarReservacion(){
	mysql_free_result(res);
	char query[500]= {0};
	int identificador;
	printf("\tDigite el identificador de reservacion a eliminar: ");
	scanf("%d",&identificador);
	snprintf(query,500,"DELETE FROM Reservacion_de_Aulas WHERE Codigo_Reservacion = \'%d\'",identificador);
	if (mysql_query(conn, query)){ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		menuOperativo();
		//exit(1);
	}else{
		printf("\tLa reservacion fue eliminada con exito\n");
		menuOperativo();
	}
}

/*****Nombre***************************************
 * mostrarAulasMasReservadas
 *****Descripción**********************************
 * Funcion encargada de obtener los datos de las 3 
 * aulas más reservadas en la base de datos y las 
 * muestra en pantalla.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void mostrarAulasMasReservadas(){
	char query[500]= {0};
	snprintf(query,500,"SELECT Nombre_Aula, COUNT(Nombre_Aula) AS RANKING FROM Reservacion_de_Aulas GROUP BY Nombre_Aula ORDER BY COUNT(Nombre_Aula) DESC");
	if (mysql_query(conn, query)){ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		menuOperativo();
		//exit(1);
	}else{
		int contador = 0;
		res = mysql_use_result(conn);

		while(contador < 3){
			row = mysql_fetch_row(res);
			if(contador == 0){
				printf("\n\tPrimer Aula mas reservada: %s \n",row[0]);
				contador ++;
			}else if (contador == 1){
				printf("\n\tSegunda Aula mas reservada: %s \n",row[0]);
				contador ++;
			}else{
				printf("\n\tTercer Aula mas reservada: %s \n",row[0]);
				contador ++;
			}
		}
		mysql_free_result(res);
	}
}

/*****Nombre***************************************
 * mostrarProfesoresMasReservados
 *****Descripción**********************************
 * Funcion encargada de obtener los datos de los 3 
 * profesores con más reservaciones en la base de datos
 * y los muestra en pantalla.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void mostrarProfesoresMasReservados(){
	char query[500]= {0};
	snprintf(query,500,"SELECT P.Nombre, COUNT(CP.Cedula_Profesor) AS RANKING FROM Reservacion_de_Aulas R INNER JOIN Cursos_por_Periodo CP ON R.Codigo_Curso = CP.Codigo_Curso AND CP.Grupo = R.Grupo AND CP.Periodo = R.Periodo AND CP.Anio = R.Año INNER JOIN Profesores P ON CP.Cedula_Profesor = P.Cedula_Profesor GROUP BY Nombre ORDER BY COUNT(CP.Cedula_Profesor) DESC");
	if (mysql_query(conn, query)){ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		menuOperativo();
		//exit(1);
	}else{
		int contador = 0;
		res = mysql_use_result(conn);
		
		while(contador < 3){
			row = mysql_fetch_row(res);
			if(contador ==0){
				printf("\n \tPrimer Profesor mas reservado: %s \n",row[0]);
				contador ++;
			}else if (contador == 1){
				printf("\n \tSegunda Profesor mas reservado: %s \n",row[0]);
				contador ++;
			}else{
				printf("\n \tTercer Profesor mas reservado: %s \n",row[0]);
				contador ++;
			}
		}
		mysql_free_result(res);
	}
}

/*****Nombre***************************************
 * mostrarReservasAnioMes
 *****Descripción**********************************
 * Funcion encargada de obtener los datos de las 
 * reservaciones y las ordena por año-mes y las muestra 
 * en pantalla.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void mostrarReservasAnioMes(){
	char query[500]= {0};
	snprintf(query,500,"select Date_format(Fecha,'%Y/%M'), COUNT(Codigo_Reservacion) AS RANKING From Reservacion_de_Aulas GROUP BY Date_format(Fecha,'%Y/%M') ORDER BY COUNT(Codigo_Reservacion) DESC");
	if (mysql_query(conn, query)){ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		menuOperativo();
		//exit(1);
	}else{
		int contador = 0;
		res = mysql_use_result(conn);
		
		while(row = mysql_fetch_row(res)){
			printf("\n \tPeriodo: %s con cantidad de reservaciones de %s  \n",row[0],row[1]);
		}
		mysql_free_result(res);
	}
}

//Consultas

/*****Nombre***************************************
 * consultaFecha
 *****Descripción**********************************
 * Funcion encargada de obtener los datos para realizar
 * la consulta por la fecha de las reservaciones, hace
 * el query de la consulta obtiene los datos y los muestra
 * en pantalla
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void consultaFecha(){
	int dia;
	int mes;
	int year;
	char query[1000];
	printf("\tDigite el dia para la reservacion: ");
	scanf("%d",&dia);
	if (dia > 31 || dia < 0){
		printf("\tEl dia indicado es incorrecto \n");
		reservarAulas();
	}
	printf("\tDigite el mes para la reservacion\n: ");
	scanf("%d",&mes);
	if (mes > 12 || mes < 1){
		printf("\tEl mes indicado es incorrecto\n");
		reservarAulas();
	}
	printf("\tDigite el anio para la reservacion\n");
	scanf("%d",&year);
	if(year > 2035 || year < 2021){
		printf("\tEl anio indicado es invalido\n");
		reservarAulas();
	}
	snprintf(query,1000,"SELECT Nombre_Aula, Codigo_Reservacion, Año, Periodo, Codigo_Curso, Grupo, Hora_Inicio, Hora_Fin from Reservacion_de_Aulas WHERE Fecha = \'%d/%d/%d\' Order By Nombre_Aula", year,mes,dia);
	if(mysql_query(conn,query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("\tFecha no encontrada");
		reservarAulas();
	}
	res = mysql_use_result(conn);
	printf("\tNombre Aula\tCodigo_Reservacion\tAnio\tPeriodo\tCodigo de Curso\tGrupo\tHora de Inicio\tHora de Fin\n");
	while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
		printf("\t%s\t\t%s\t\t\t%s\t%s\t%s\t\t%s\t%s\t%s\n", row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
	menuAdministrativo();
}

/*****Nombre***************************************
 * consultaAula
 *****Descripción**********************************
 * Funcion encargada de obtener los datos para realizar
 * la consulta por el nombre del aula de las reservaciones, hace
 * el query de la consulta obtiene los datos y los muestra
 * en pantalla.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void consultaAula(){
	char nombreAula[10];
	char query[1000];
	printf("\tDigite el nombre del aula:");
	scanf("%s",&nombreAula);
	snprintf(query,1000,"SELECT Fecha,Hora_Inicio, Hora_Fin, Codigo_Reservacion, Anio, Periodo, Codigo_Curso, Grupo from Reservacion_de_Aulas WHERE Nombre_Aula = \'%s\' Order By Fecha asc, Hora_Inicio", nombreAula);
	if(mysql_query(conn,query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("\tAula no encontrada");
		reservarAulas();
	}
	res = mysql_use_result(conn);
	printf("\tFecha\t\tHora de Inicio\tHora de Fin\tCodigo_Reservacion\tAnio\tPeriodo\tCodigo de Curso\tGrupo\n");
	while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
		printf("\t%s\t%s\t%s\t%s\t\t\t%s\t%s\t%s\t\t%s\n", row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
	menuAdministrativo();
}

/*****Nombre***************************************
 * consultaCurso
 *****Descripción**********************************
 * Funcion encargada de obtener los datos para realizar
 * la consulta por el el curso por periode de las reservaciones, 
 * hace el query de la consulta obtiene los datos y los muestra
 * en pantalla.
 *****Retorno**************************************
 * N/A
 *****Entradas*************************************
 * N/A
 **************************************************/

void consultaCurso(){
	int year;
	int periodo;
	int codigoCurso;
	int grupo;
	char query[1000];
	printf("\tDigite el anio del curso: ");
	scanf("%d",&periodo);
	printf("\tDigite el periodo del curso: ");
	scanf("%d",&periodo);
	if (periodo < 0 || periodo > 2){
		printf("\tPeriodo indicado es invalido\n");
		reservarAulas();
	}
	printf("\tDigite el codigo del curso:");
	scanf("%d",&codigoCurso);
	printf("\tDigite el grupo del curso:");
	scanf("%d",&grupo);
	snprintf(query,1000,"SELECT Codigo_Reservacion, Fecha, Hora_Inicio, Hora_Fin, Nombre_Aula from Reservacion_de_Aulas WHERE Año = \'%d\' AND Periodo = \'%d\' AND Codigo_Curso = \'%d\' AND Grupo = \'%d\' Order By Fecha, Hora_Inicio, Nombre_Aula", year,periodo,codigoCurso,grupo);
	if(mysql_query(conn,query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("\tCurso no encontrado");
		reservarAulas();
	}else{
		res = mysql_use_result(conn);
		printf("\tCodigo_Reservacion\tFecha\tHora de Inicio\tHora de Fin\tNombre Aula\n");
		while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
		{
			printf("\t%s\t\t%s\t%s\t%s\t%s\n", row[0],row[1],row[2],row[3],row[4]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
		}
		menuAdministrativo();
	}
}




