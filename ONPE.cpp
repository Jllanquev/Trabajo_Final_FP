#include <iostream>
#include <string>
using namespace std;

struct Correo{
	string User;
	string  Domain;
};

struct Datos{
	string Nombre;
	string Sexo;
	string PartidoPo;
	int Edad;
	Correo Email;
	int Dni;
	string Lema;
};

void LeerCorreo(Correo &, string, string);
void LeerUser(Datos &,string,string,string,int,Correo,int,string);

int main(){
	int Opcion,edad,dni,n=0;
	string sexo,partido,nombre,correo,dom,lema;
	Datos User[200], cont;
	cout<<"*****************************************************"<<endl;
	cout<<"                          ONPE                      "<<endl;
	cout<<"*****************************************************"<<endl;
	cout<<"1. Inscripcion de candidatos"<<endl;
	cout<<"2. Mostrar lista de candidatos"<<endl;
	cout<<"3. Eliminar candidato"<<endl;
	cout<<"4. Elecciones"<<endl;
	cout<<"5. Resultados"<<endl;
	cout<<"6. Salir"<<endl;
	cout<<"Ingrese su opcion: "; cin>>Opcion;
	
	switch (Opcion){
		case 1:
			system ("cls");
			cout<<"***********************************************************"<<endl;
			cout<<"                     INSCRIPCION                           "<<endl;
			cout<<"***********************************************************"<<endl;
			cout<<"Ingrese los datos:  "<<endl;
			cout<<"Nombre: "; cin>>nombre;
			cout<<"Sexo: "; cin>>sexo;
			cout<<"PartidoPo";cin>>partido;
			cout<<"Edad: ";cin>>edad;
			cout<<"Usuario del correo: "; cin>>correo;
			cout<<"Dominio del correo: "; cin>>dom;
			cout<<"Dni: ";
			cout<<"Lema: "<<endl;
			
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			break;
	}
}
