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
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
            cout << "No. Filas:" << tuplas << endl;
            cout << "No. Columnas:" << campos << endl;

            cout << "Los nombres de las columnas son:" << endl;
 	    cout << "--------------------------------" << endl;

            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << " | ";
            }

            cout << endl << "--------------------------------" << endl;

            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    cout << PQgetvalue(result,i,j) << " | ";
                }
                cout << endl;
            }
        }

}

void Conexion::CrearVista(const char *consulta){
result = PQexec(cnn, consulta);

if (result != NULL) {
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
     
            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << " | ";
            }

            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    cout << PQgetvalue(result,i,j) << " | ";
                }
                cout << endl;
            }
        }
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
