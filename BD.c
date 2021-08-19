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
	
	printf("Digite el nombre del profesor: ");
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
	menuOperativo();
}

void borrarTodo(){
	if (mysql_query(conn, "DELETE from Profesores"))
	{ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
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
