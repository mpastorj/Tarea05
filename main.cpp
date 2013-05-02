#include <iostream>
#include <cstring>
#include <libpq-fe.h>
#include "Conexion.cpp"

using namespace std;


#define VERSION "Version 1.0 Fecha y hora de compilación: " __DATE__ " " __TIME__ ;

int main(int argc, char* argv[])
{

cout << "INTEGRANTES: " << endl;
cout <<"- Marilyn Pastor Jaque"<< endl; 
cout <<"- Monica Riquelme" << endl;
cout <<"- Pedro Cuevas Meza" << endl;

Conexion cn ;

cn.conectar();



if(strcmp(argv[1], "-s") == 0){
cn.consulta("SELECT c.asignatura AS ASIGNATURA,ROUND(AVG(a.nota),5) AS PROMEDIO, ROUND(STDDEV(a.nota),5) AS DESVIACION from asignaturas_cursadas a, cursos c WHERE a.curso_id=c.curso_id GROUP BY c.asignatura");
}
else if(strcmp(argv[1],"-v") == 0){
cout << VERSION ;
cout << endl;
cn.consulta("select LOCALTIMESTAMP(0) as Fecha_y_hora_actual");
}
else if(strcmp(argv[1],"-a") == 0){
cn.consulta("SELECT ROUND((AVG(a.nota)),1) AS ESTIMADO,a.estudiante_id from asignaturas_cursadas a, cursos c WHERE a.curso_id=c.curso_id AND c.asignatura <> 'CÁLCULO VECTORIAL' GROUP BY estudiante_id ORDER BY estudiante_id");
cn.ExportarArchivo();
}

cn.desconectar();

}
