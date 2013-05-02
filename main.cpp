#include <iostream>
#include <libpq-fe.h>
#include "Conexion.cpp"

using namespace std;

int main()
{

cout << "INTEGRANTES: " << endl;
cout <<"- Marilyn Pastor Jaque"<< endl; 
cout <<"- Monica Riquelme" << endl;
cout <<"- Pedro Cuevas Meza" << endl;
Conexion cn ;

cn.conectar();


/*cn.consulta("SELECT * FROM cursos");*/

cn.consulta("SELECT c.asignatura AS ASIGNATURA,ROUND(AVG(a.nota),5) AS PROMEDIO, ROUND(STDDEV(a.nota),5) AS DESVIACION from asignaturas_cursadas a, cursos c WHERE a.curso_id=c.curso_id GROUP BY c.asignatura");


cn.desconectar();

}
