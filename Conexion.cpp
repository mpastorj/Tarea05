#include <iostream>
#include <libpq-fe.h>

using namespace std;

PGconn *cnn = NULL;
PGresult *result = NULL;
FILE *archivo;

class Conexion{

 int i;

 public:

 void conectar();
 void consulta(const char *consulta);
 void CrearVista(const char *consulta); 
 void ExportarArchivo();   
 void desconectar();
 void DestruirVista();   

};


void Conexion::conectar(){

cnn = PQsetdbLogin("sebastian.cl","5432",NULL,NULL,"iswdb","isw","isw"); // Se crea la conexión con los datos de nuestro servidor
if (PQstatus(cnn) != CONNECTION_BAD) {
        cout << "Estamos conectados a PostgreSQL!" << endl;
        }
else {
        cout << "Error de conexion" << endl;
    }

}


void Conexion::consulta(const char *consulta){

result = PQexec(cnn, consulta);

if (result != NULL) {
            int columnas = PQntuples(result);
            int filas = PQnfields(result);

 	    cout << "--------------------------------" << endl;

            for (i=0; i<filas; i++) {
                cout << PQfname(result,i) << " | ";
            }

            cout << endl << "--------------------------------" << endl;

            for (i=0; i<columnas; i++) {
                for (int j=0; j<filas; j++) {
                    cout << PQgetvalue(result,i,j) << " | ";
                }
                cout << endl;
            }
        }

}

void Conexion::CrearVista(const char *consulta){
result = PQexec(cnn, consulta);
}


void Conexion::ExportarArchivo(){

archivo = fopen ( "estimaciones.csv", "w" );

PQprintOpt  options = {0};

                
options.fieldSep = (char *) ",";  /* field separator */

PQprint( archivo, result, &options );

fclose ( archivo );


}

void Conexion::desconectar(){

   PQclear(result);
   PQfinish(cnn);

cout<<endl<<"Conexión finalizada..."<<endl;

}

void Conexion::DestruirVista(){

 PQclear(result);
}
