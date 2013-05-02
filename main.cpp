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


cn.consulta("SELECT * FROM cursos");


cn.desconectar();

}
