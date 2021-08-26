#include <stdio.h>
#include <mysql.h> 
#include <string.h>

/* libreria que nos permite hacer el uso de las conexiones y consultas con MySQL */
MYSQL *conn; /* variable de conexión para MySQL */
MYSQL_RES *res; /* variable que contendra el resultado de la consuta */
MYSQL_ROW row; /* variable que contendra los campos por cada registro consultado */

char *server = "localhost"; /*direccion del servidor 127.0.0.1, localhost o direccion ip */
char *user = "root"; /*usuario para consultar la base de datos */
char *password = "Uzumakii2011"; /* contraseña para el usuario en cuestion */
char *database = "Sistema_Administracion_Aulas"; /*nombre de la base de datos a consultar */

void conectarBaseDatos(){
	conn = mysql_init(NULL); /*inicializacion a nula la conexión */
	/* conectar a la base de datos */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{ /* definir los parámetros de la conexión antes establecidos */
		fprintf(stderr, "%s\n", mysql_error(conn)); /* si hay un error definir cual fue dicho error */
		exit(1);
	}
}

void desconectarBaseDatos(){
		/* se libera la variable res y se cierra la conexión */
	mysql_free_result(res);
	mysql_close(conn);
}

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

void incluirProfesor(){
	char nombre [30];
	int cedula;
	char query[200]= {0};
	printf("Digite la cedula del profesor: ");
	scanf("%d", &cedula);
	while(getchar()!='\n');
	
	printf("Digite el nombre del profesor: \n");
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
	printf("El profesor fue incluido con exito");
	menuOperativo();
}

void borrarTodo(){
	if (mysql_query(conn, "DELETE from Profesores"))
	{ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	printf("Los profesores fueron borrados con exito");
}

void listarCursos(){
	/* enviar consulta SQL */
	mysql_query(conn, "select * from Cursos");
	res = mysql_use_result(conn);
	printf("\tNombre\t\tCodigo_Curso\tCodigo_Carrera\n");
	while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
		printf("\t%s\t%s\t%s\n", row[0],row[1],row[2]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
	menuOperativo();
}
void incluirCursos(){
	int codigoCurso;
	int year; 
    int periodo;
    int grupo;
    int cedulaProfe;
    int cantEstudiante;
	char query[500]= {0};
	printf("Digite el codigo del curso: ");
	scanf("%d", &codigoCurso);
	while(getchar()!='\n');
	printf("Digite el anio: ");
	scanf("%d", &year);
	while(getchar()!='\n');
    if(year > 2035 || year < 2021){
        printf("EL anio debe ser mayor o igual a 2021 o menor a 2035");
        incluirCursos();
    }
    printf("Digite el periodo: ");
	scanf("%d", &periodo);
	while(getchar()!='\n');
    if(periodo == 1 || periodo == 2){
        printf("Digite el grupo: ");
	    scanf("%d", &grupo);
	    while(getchar()!='\n');
        printf("Digite la cedula del profesor: ");
	    scanf("%d", &cedulaProfe);
	    while(getchar()!='\n');
        printf("Digite la cantidad de estudiantes: ");
	    scanf("%d", &cantEstudiante);
	    while(getchar()!='\n');
    }else{
        printf("El periodo indicado es invalido \n");
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
	printf("El curso fue agregado al periodo indicado");
	menuOperativo();
}
void listarCursosPeriodo(){
	/* enviar consulta SQL */
	mysql_query(conn, "select * from Cursos_por_Periodo");
	res = mysql_use_result(conn);
	printf("\tCodigoCurso\tPeriodo\tAnio\tGrupo\tCedulaProfesor\tCantidadEstudiantes\n");
	while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
		printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", row[0],row[1],row[2],row[3],row[4],row[5]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
	menuOperativo();
}	
void borrarCursoPeriodo(){
	int codigoCurso;
	int year; 
    int periodo;
    int grupo;
	char query[500]= {0};
	printf("Digite el codigo del curso: ");
	scanf("%d", &codigoCurso);
	while(getchar()!='\n');
	printf("Digite el anio: ");
	scanf("%d", &year);
	while(getchar()!='\n');
	printf("Digite el periodo: ");
	scanf("%d", &periodo);
	while(getchar()!='\n');
	printf("Digite el grupo: ");
	scanf("%d", &grupo);
	while(getchar()!='\n');
	snprintf(query,500,"DELETE FROM Cursos_por_Periodo WHERE Codigo_Curso = \'%d\' AND Periodo = \'%d\' AND Anio = \'%d\' AND Grupo = \'%d\'", codigoCurso, periodo,year,grupo);
	if (mysql_query(conn, query));
	{ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		menuOperativo();
		//exit(1);
	}
	printf("El curso fue eliminado del periodo indicado");
}

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
		printf("No se pudo abrir el archivo... \n"); 
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
						printf("Token: %s\n", aula);
						if (isalpha(aula[0])){
							printf("SI es letra");
							int cont = 1;
							int largo = strlen(aula)-1;
							while (cont <= largo){
								if(isdigit(aula[cont])){
									printf("SI es NUmero");
									cont+=1;
								}else{
									printf("NO es numero");
									printf("EL nombre del aula: %s no cumple el formato \n",aula);
									printf("Se seguiran insertando las aulas si el formato es correcto\n");
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
						printf("La cantidad de estudiantes excede la maxima capacidad del aula \n");
						banderaError= 3;
						break;
					}else{
						int cont = 0;
						int largo = strlen(canESt)-1;
						while (cont <= largo){
							if(isdigit(canESt[cont])){
								printf("SI");
								cont+=1;
							}else{
								printf("NO");
								printf("La capacidad indicada %s no cumple la capacidad maxima del aula \n",canESt);
								printf("Se seguiran insertando las aulas si el formato es correcto\n");
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
	printf("Se agregaron las aulas que no estan repetidas y las que cumplen el formato");
	fclose(archivo);
}

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

	printf("Digite el dia para la reservacion: ");
	scanf("%d",&dia);
	if (dia > 31 || dia < 0){
		printf("El dia indicado es incorrecto \n");
		reservarAulas();
	}
	printf("Digite el mes para la reservacion\n: ");
	scanf("%d",&mes);
	if (mes > 12 || mes < 1){
		printf("El mes indicado es incorrecto\n");
		reservarAulas();
	}
	printf("Digite el anio para la reservacion\n");
	scanf("%d",&year);
	if(year > 2035 || year < 2021){
		printf("El anio indicado es invalido\n");
		reservarAulas();
	}
	printf("Digite la hora de inicio de la reservacion: ");
	scanf("%d",&horaInicio);
	if (horaInicio < 0 || horaInicio > 23){
		printf("HOra de inicio indicada es invalida\n");
		reservarAulas();
	}
	printf("Digite los minutos para la reservacion: ");
	scanf("%d",&minutosInicio);
	if(minutosInicio < 0 || minutosInicio > 59){
		printf("Los minutos indicados son invalidos\n");
		reservarAulas();
	}
	printf("Digite la hora final de la reservacion: ");
	scanf("%d",&horaFin);
	if (horaFin < 0 || horaFin > 23){
		printf("LA hora indicada no es valida\n");
		reservarAulas();
	}
	printf("Digite los minutos finales para la reservacion: ");
	scanf("%d",&minutosFin);
	if(minutosFin < 0 || minutosFin > 59){
		printf("Los minutos indicados son invalidos\n");
		reservarAulas();
	}
	if(horaInicio >= horaFin){
		printf("Las horas indicadas son invalidas\n");
		reservarAulas();
	}
	printf("Digite el nombre del aula:");
	scanf("%s",&nombreAula);
	
	printf("Digite el periodo de reservacion: ");
	scanf("%d",&periodo);
	if (periodo < 0 || periodo > 2){
		printf("Periodo indicado es invalido\n");
		reservarAulas();
	}

	printf("Digite el codigo del curso:");
	scanf("%d",&codigoCurso);

	printf("Digite el grupo del curso:");
	scanf("%d",&grupo);
	
	snprintf(query,1000,"SELECT Capacidad from Aulas WHERE Nombre_Aula = \'%s\'", nombreAula);
	if(mysql_query(conn,query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("AUla no encontrada");
		reservarAulas();
	}
	res = mysql_use_result(conn);
	row = mysql_fetch_row(res);
	capacidadAula = atoi(row[0]);
	mysql_free_result(res);

	snprintf(query,1000,"SELECT Cantidad_Estudiantes from Cursos_por_Periodo WHERE Codigo_Curso = \'%d\' AND Periodo = \'%d\' AND Anio = \'%d\' AND Grupo = \'%d\'", codigoCurso, periodo,year,grupo);
	if(mysql_query(conn,query)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		//printf("Curso no enconrado");
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
		printf("El codigo de su reservacion es: %d \n",codActual+1);
		codActual ++;
	}else{
		int cupos = capacidadCurso - capacidadAula;
		snprintf(query,1000,"INSERT INTO Reservacion_de_Aulas(Codigo_Reservacion,Fecha,Hora_Inicio,Hora_Fin,Codigo_Curso,Periodo,Año,Grupo,Nombre_Aula) VALUES (NULL,\'%d/%d/%d\',\'%d:%d:00\',\'%d:%d:00\',\'%d\',\'%d\',\'%d\',\'%d\',\'%s\')",year,mes,dia,horaInicio,minutosInicio,horaFin,minutosFin,codigoCurso,periodo,year,grupo,nombreAula);
		/* definicion de la consulta y el origen de la conexion */
		if(mysql_query(conn, query)){
			fprintf(stderr, "%s\n", mysql_error(conn));
        	reservarAulas();
		}
		printf("El codigo de su reservacion es: %d \n",codActual+1);
		codActual ++;
		while(cupos > 0){
			char nombreAula[3];
			printf("\nSe necesita un aula mas porque la cantidad de estudiantes supera el limite del aula \n");
			printf("Digite el nombre del aula:");
			scanf("%s",&nombreAula);
			int capacidad;
			snprintf(query,1000,"SELECT Capacidad from Aulas WHERE Nombre_Aula = \'%s\'", nombreAula);
			if(mysql_query(conn,query)){
				fprintf(stderr, "%s\n", mysql_error(conn));
				printf("AUla no encontrada \n");
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
					printf("El codigo de su reservacion es: %d\n",codActual+1);
					codActual ++;
				}
				
			}
			
		}
		menuOperativo();
	}
}

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



