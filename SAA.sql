CREATE DATABASE Sistema_Administracion_Aulas2;

Use Sistema_Administracion_Aulas2;

CREATE TABLE Aulas
(
Nombre_Aula Varchar(6) primary key not null,
Capacidad int
);
 
CREATE TABLE Profesores
(
Nombre Varchar(55),
Cedula_Profesor int primary key not null
);

 
CREATE TABLE Cursos
(
Nombre Varchar(55),
Codigo_Curso int primary key not null,
Codigo_Carrera int not null
);

 
CREATE TABLE Cursos_por_Periodo(
Codigo_Curso int not null, 
Periodo int not null,
Año int not null, 
Grupo int not null, 

Cedula_Profesor int not null, 
Cantidad_EStudiantes int not null, 

Primary Key(Codigo_Curso,Periodo,Año,Grupo), 
FOREIGN KEY(Codigo_Curso) REFERENCES Cursos(Codigo_Curso), 
FOREIGN KEY(Cedula_Profesor) REFERENCES Profesores(Cedula_Profesor));


CREATE TABLE Reservacion_de_Aulas(
Codigo_Reservacion int not null auto_increment,

Fecha date not null, 
Hora_Inicio time not null, 
Hora_fin time not null, 

Codigo_Curso int not null, 
Periodo int not null, 
Año int not null, 
Grupo int not null, 

Nombre_Aula VARCHAR(6) Not null,

Primary Key (Fecha, Hora_Inicio, Hora_Fin, Nombre_Aula), 
FOREIGN KEY(Codigo_Curso,Periodo,Año,Grupo) REFERENCES Cursos_por_Periodo(Codigo_Curso,
Periodo,Año,Grupo), index(Codigo_Reservacion));

Insert Into Cursos(Nombre, Codigo_Curso, Codigo_Carrera) VALUES
("Requerimientos de Software", 1, 506),
("Lenguajes de Programacion", 2, 506),
("Matematica discreta", 3, 506),
("Administracion de Proyectos", 4, 506),
("Analisis de Algoritmos", 5, 506),
("Estructuras de datos", 6, 506),
("Fisica 1", 7, 504),
("Elementos de computacion", 8, 504),
("Fisica 2", 9, 504),
("Algebra lineal", 10, 506),
("Ingles 1", 11, 504),
("Ingles 2", 12, 504),
("Comunicacion Escrita", 13, 504),
("Compiladores e interpretes", 14, 506),
("Diseño de software", 15, 506),
("Calculo Diferencial e Integral", 16, 506),
("Probabilidades", 17, 506),
("Estadistica", 18, 506),
("Introduccion de programacion", 19, 504),
("Arquitectura de computadores", 20, 504);



