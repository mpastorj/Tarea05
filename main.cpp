#include <iostream>
#include <cstring>
#include <libpq-fe.h>
#include "Conexion.cpp"

using namespace std;


#define VERSION "Version 1.0 Fecha y hora de compilacion: " __DATE__ " " __TIME__ ;

int main(int argc, char* argv[])
{

  Conexion cn ;

  cn.conectar();

  cout << argv[1];

  if (argc > 1)
    {

      if (strcmp(argv[1], "-i") == 0)
        {

          cn.CrearVista("CREATE OR REPLACE VIEW NOTAREAL AS SELECT a.nota AS REAL from asignaturas_cursadas a, cursos c where estudiante_id=argv[2] AND a.curso_id=c.curso_id AND c.asignatura='CÁLCULO VECTORIAL'");

          cn.CrearVista("CREATE OR REPLACE VIEW NOTAESTIMADA AS SELECT a.nota AS ESTIMADO from asignaturas_cursadas a, cursos c WHERE a.estudiante_id=argv[2] AND a.curso_id=c.curso_id AND c.asignatura <> 'CÁLCULO VECTORIAL'");

          cn.consulta("SELECT AVG(ESTIMADO) AS Nota_Estimada , AVG(REAL) AS Nota_real from NOTAESTIMADA, NOTAREAL");

          cn.consulta("DROP VIEW NOTAESTIMADA");

          cn.consulta("DROP VIEW NOTAREAL");

        }

      else if (strcmp(argv[1], "-s") == 0)
        {
          cn.consulta("SELECT c.asignatura AS ASIGNATURA,ROUND(AVG(a.nota),5) AS PROMEDIO, ROUND(STDDEV(a.nota),5) AS DESVIACION from asignaturas_cursadas a, cursos c WHERE a.curso_id=c.curso_id GROUP BY c.asignatura");
        }
      else if (strcmp(argv[1],"-v") == 0)
        {
          cout << "INTEGRANTES: " << endl;
          cout <<"- Marilyn Pastor Jaque"<< endl;
          cout <<"- Monica Riquelme Vasquez" << endl;
          cout <<"- Pedro Cuevas Meza" << endl;
          cout << VERSION ;
          cout << endl;
          cn.consulta("select LOCALTIMESTAMP(0) as Fecha_y_hora_actual");
        }
      else if (strcmp(argv[1],"-a") == 0)
        {
          cn.consulta("SELECT ROUND((AVG(a.nota)),1) AS ESTIMADO,a.estudiante_id from asignaturas_cursadas a, cursos c WHERE a.curso_id=c.curso_id AND c.asignatura <> 'CÁLCULO VECTORIAL' GROUP BY estudiante_id ORDER BY estudiante_id");
          cn.ExportarArchivo();
        }
    }
  else
    {
      cout << "Información sobre el uso del software: Para utilizar este programa primero "<< endl;
      cout << "se debe ingresar alguna de las opciones en la línea de comandos" << endl;
      cout << "Si ordena al programa que se ejecute la opción '-i id' donde id es el "<< endl;
      cout << "estudiante este debe mostrar la nota estimada de aprobación" << endl;
      cout << "Además en una columna adicional, debe mostrar la nota realmente obtenida" << endl;
      cout << "Si ordena al programa que se ejecute la opción '-a' este debe hacer la "<< endl;
      cout << "estimación para todos los estudiantes, y lo guardará en un archivo de "<< endl;
      cout << "texto(estimaciones.csv) en forma ascendente" << endl;
      cout << "Si ordena al programa que se ejecute la opción '-s' deberá mostrar el "<< endl;
      cout << "promedio y la desviación estándar de cada una de las asignaturas" << endl;
      cout << "Si ordena al programa que se ejecute la opción '-v' debe mostrar la fecha "<< endl;
      cout << "y hora de compilación, la fecha y hora actual, la versión del programa y "<< endl;
      cout << "el nombre de los integrantes del grupo de trabajo" << endl;
    }

  cn.desconectar();

}
