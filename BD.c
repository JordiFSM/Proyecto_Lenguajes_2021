#include <stdio.h>
#include <mysql.h> 

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
    if(year > 2035 || year < 1974){
        printf("EL anio debe ser mayor a 1974 o menor a 2035");
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
