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
	int Opcion,edad,dni,n=0,cand;
	string sexo,partido,nombre,user,dom,lema;
	Datos User[200], cont;
	Correo Email;

	
	do{
		system("cls");
		cout<<"*****************************************************"<<endl;
		cout<<"                          ONPE                      "<<endl;
		cout<<"*****************************************************"<<endl;
		cout<<"1. Inscripcion de candidatos"<<endl;
		cout<<"2. Modificar candidato"<<endl;
		cout<<"3. Mostrar lista de candidato"<<endl;
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
				cin.ignore();
				cout<<"Nombre: "; getline(cin,nombre);
				cout<<"Sexo (M|F): "; cin>>sexo;
				cin.ignore();
				cout<<"PartidoPo: ";getline(cin,partido);
				cout<<"Edad: ";cin>>edad;
				cout<<"Dni: "; cin>>dni;
				cin.ignore();
				cout<<"Lema: ";getline(cin,lema);
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
				system("cls");
				cout<<"****************************************************"<<endl;
				cout<<"                 MENU DE MODIFICACIONES             "<<endl;
				cout<<"****************************************************"<<endl<<endl;
				cout<<"NUMERO DE ORDEN"<<"\t->\t"<<"CANDIDATOS"<<"\t-\t"<<"PARTIDO POLITICO"<<endl;
				for(int i=0;i<n;i++){
					cout<<"Candidato #"<<i+1<<"\t\t->\t"<<User[i].Nombre<<"\t-\t"<<User[i].PartidoPo<<endl;
				}
				cout<<endl;
				cout<<"Inserte el numero de orden del candidato a modificar:   "; cin>>Opcion;
				cand = (Opcion-1);
				//Casos en menu de opciones con do-while para poder volver al menu principal :D
				do{
					system("cls");
					cout<<"****************************************************"<<endl;
					cout<<"                 MENU DE MODIFICACIONES             "<<endl;
					cout<<"****************************************************"<<endl<<endl;
					cout<<"\tCandidato #"<<(cand+1)<<":"<<endl;
					cout<<"Nombre: \t\t"<<User[cand].Nombre<<endl;
					cout<<"Sexo: \t\t\t"<<User[cand].Sexo<<endl;
					cout<<"Partido politico: \t"<<User[cand].PartidoPo<<endl;
					cout<<"Edad: \t\t\t"<<User[cand].Edad<<endl;
					cout<<"DNI: \t\t\t"<<User[cand].Dni<<endl;
					cout<<"Lema: \t\t\t"<<User[cand].Lema<<endl;
					cout<<"Correo electronico:\t"<<User[cand].Email.user<<"@"<<User[cand].Email.domain<<endl<<endl;
					
					cout<<"PARAMETROS A MODIFICAR:"<<endl;
					cout<<"1. Nombre del candidato"<<endl;
					cout<<"2. Sexo del candidato"<<endl;
					cout<<"3. Partido politico"<<endl;
					cout<<"4. Edad del candidato"<<endl;
					cout<<"5. DNI del candidato"<<endl;
					cout<<"6. Lema del candidato"<<endl;
					cout<<"7. Email del candidato"<<endl;
					cout<<"8. Volver al menu principal"<<endl<<endl;
					cout<<"Ingrese su opcion: "; cin>>Opcion;
					switch (Opcion){
						case 1:
							system("cls");
							cout<<"Inserte el nombre modificado del candidato:"<<endl;
							cin.ignore();
							cout<<"Nombre: "; getline(cin,User[cand].Nombre);
							break;							
						case 2:
							system("cls");
							cout<<"Inserte el sexo modificado del candidato:"<<endl;
							cout<<"Sexo (M|F): "; cin>>User[cand].Sexo;
							break;
						case 3:
							system("cls");
							cout<<"Inserte el Partido politico modificado del candidato:"<<endl;
							cin.ignore();
							cout<<"PartidoPo: ";getline(cin,User[cand].PartidoPo);
							break;
						case 4:
							system("cls");
							cout<<"Inserte la edad modificada del candidato:"<<endl;
							cout<<"Edad: ";cin>>User[cand].Edad;
							break;
						case 5:
							system("cls");
							cout<<"Inserte el DNI modificado del candidato:"<<endl;
							cout<<"DNI: "; cin>>User[cand].Dni;
							break;
						case 6:
							system("cls");
							cout<<"Inserte el lema modificado del candidato:"<<endl;
							cin.ignore();
							cout<<"Lema: ";getline(cin,User[cand].Lema);
							break;
						case 7:
							system("cls");
							cout<<"Ingrese el correo electronico modificado (Usuario@dominio): "<<endl;
							cout<<"\tUsuario del correo: "; cin>>User[cand].Email.user;
							cout<<"\tDominio del correo: "; cin>>User[cand].Email.domain;
							break;
						case 8:
							break;
						default:
							cout<<"ERROR: Ocion fuera de los parametros, INTENTE OTRA VEZ !!!"<<endl;
							system("pause");
							break;
					}
				} while (Opcion != 8);
				break;
			case 3:
				system("cls");
				cout<<"*****************************************************"<<endl;
				cout<<"                   LISTA DE CANDIDATOS               "<<endl;
				cout<<"*****************************************************"<<endl<<endl;
				
				for( int i = 0 ; i < n ; i++ ){
					cout<<"\tCANDIDATO #"<<(i+1)<<":"<<endl;
					cout<<"Nombre: \t\t"<<User[i].Nombre<<endl;
					cout<<"Sexo: \t\t\t"<<User[i].Sexo<<endl;
					cout<<"Partido politico: \t"<<User[i].PartidoPo<<endl;
					cout<<"Edad: \t\t\t"<<User[i].Edad<<endl;
					cout<<"DNI: \t\t\t"<<User[i].Dni<<endl;
					cout<<"Lema: \t\t\t"<<User[i].Lema<<endl;
					cout<<"Correo electronico:\t"<<User[i].Email.user<<"@"<<User[i].Email.domain<<endl<<endl;
				}
				system("pause");
				break;
			case 4:
			case 5:
			case 6:
				break;
		}
	}while(Opcion!=6);
	return 0;
}

void LeerCorreo(Correo &a, string b,string c){
	a.user=b;
	a.domain=c;
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

