#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum EstadoCandidato { PENDIENTE, APTO, OBSERVADO };

struct Correo {
    string user;
    string domain;
};

struct Candidato {
    int numero;               
    string nombreCompleto;
    char sexo;
    int edad;
    int dni;
    Correo email;
    string partidoPolitico;
    string observaciones;        
    EstadoCandidato estado = PENDIENTE;
    int votos = 0;             
};

struct MesaDeVotacion {
    int numeroMesa;                 
    string distrito;               
     vector<int> dnisAsignados;
    int votosEmitidos = 0;          
    int capacidad = 500;             
};
struct Votante {
    string dni;
    string nombre;
    int edad;
    int numeroMesa;         
    bool haVotado = false;
};
struct ResultadoFinal {
    string nombreCandidato;
    string partido;
    int votos;
    float porcentaje;
    bool clasificaSegundaVuelta = false;
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
void LeerUser(Datos &,string,string,string,int,int,Correo,string);

int main(){
	int Opcion,edad,dni,n=0;
	string sexo,partido,nombre,user,dom,lema;
	Datos User[200], cont;
	Correo Email;
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
			cout<<"Sexo (M|F): "; cin>>sexo;
			cout<<"PartidoPo: ";cin>>partido;
			cout<<"Edad: ";cin>>edad;
			cout<<"Dni: "; cin>>dni;
			cout<<"Lema: "; cin>>lema;
			cout<<"Ingrese el correo electronico (Usuario@dominio): "<<endl;
			cout<<"\tUsuario del correo: "; cin>>user;
			cout<<"\tDominio del correo: "; cin>>dom;

			LeerCorreo(Email,user,dom);
			LeerUser(cont,nombre,sexo,partido,edad,dni,Email,lema);

			User[n] = cont;
			n++;
			system ("pause");
			break;
			
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			break;
	}
	return 0;
}

void LeerCorreo(Correo &a, string b,string c){
	a.User=b;
	a.Domain=c;
}
void LeerUser(Datos &a,string b,string c,string d,int e,int f,Correo g,string h){
	a.Nombre=b;
	a.Sexo=c;
	a.PartidoPo=d;
	a.Edad=e;
	a.Dni=f;
	a.Email=g;
	a.Lema=h;
	
}
	

