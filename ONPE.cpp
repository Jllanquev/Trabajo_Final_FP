#include<iostream>
#include<string>

using namespace std;

enum EstadoCandidato { PENDIENTE, APTO, OBSERVADO };

struct Correo {
    string user;
    string dom;
};

struct Candidato {
    int numero;               
    string nomCompleto;
    char sexo;
    int edad;
    string dni;
    Correo email;
    string PartidoPo;
    string lema;
    string observaciones;        
    EstadoCandidato estado = PENDIENTE;
    int votos = 0;             
};

struct MesaDeVotacion {
    int numMesa;                 
    string distrito;               
    int dniAsig[500];
    int votosEmitidos = 0;          
    int capacidad = 500;             
};
struct Votante {
    string dni;
    string nombre;
    int edad;
    int n_mesa;         
    bool haVotado = false;
};
struct ResultadoFinal {
    string nombreCandidato;
    string partido;
    int votos;
    float porcentaje;
    bool SegundaVuelta = false;
};

void LeerCorreo(Correo &, string, string);  //Leera el correo
void LeerCandidato(Candidato &,string,char,int,string,string,string,Correo);  //Leera los datos del candidato
void ImprimeCandidato(Candidato &);

int main(){
    int opcion,cand,edad,n=0;
	string partido,nombre,user,dom,dni,lema;
    char sexo;
	Candidato User[200], InfoCand;
	Correo email;
    do{
     cout<<"*****************************************************"<<endl;
	cout<<"                           ONPE                      "<<endl;
	cout<<"*****************************************************"<<endl;
	cout<<"1. Inscripcion de candidatos"<<endl;
    cout<<"2. Modificar candidato"<<endl;
	cout<<"3. Mostrar lista de candidatos"<<endl;
    cout<<"4. Revision de candidatos"<<endl;
	cout<<"5. Eliminar candidato"<<endl;
	cout<<"6. Proceso de elecciones"<<endl;
	cout<<"7. Resultados"<<endl;
	cout<<"0. Salir"<<endl;
	cout<<"Ingrese su opcion: "; cin>>opcion;
    switch (opcion){
		case 1:
			system ("cls");
			cout<<"***********************************************************"<<endl;
			cout<<"                     INSCRIPCION                           "<<endl;
			cout<<"***********************************************************"<<endl;
			cout<<"Ingrese los datos para la inscripcion del cantidato:  "<<endl;
            cout<<endl;
            cin.ignore();
            cout<<"Nombres completos: "; getline(cin,nombre);
			cout<<"Sexo (M|F): "; cin>>sexo;
			cout<<"Edad: ";cin>>edad;
            cin.ignore();
			cout<<"Dni: "; cin>>dni;
            cin.ignore();
            cout<<"Partido Politico: ";getline(cin,partido);
			cout<<"Lema: "; getline(cin,lema);
			cout<<"Ingrese el correo electronico (Usuario@dominio): "<<endl;
			cout<<"\tUsuario del correo: "; cin>>user;
			cout<<"\tDominio del correo: "; cin>>dom;
            cout<<endl;
            cout<<"Ha ingreso la siguiente informacion:"<<endl;
            LeerCorreo(email,user,dom);
            LeerCandidato(InfoCand,nombre, sexo, edad, dni,partido, lema, email);
            ImprimeCandidato(InfoCand);
            cout<<endl;
				char opc;
				cout<<"Esta informacion es correcta? (S/N): "; cin>>opc;
				if(opc=='S'|| opc=='s'){
					User[n] = InfoCand;
             	    n++;
             	    cout << "\033[32mLa inscripcion ha sido exitosa\033[0m" << endl;
             	    cout<<endl;
				}
				else{
					cout<<"\033[31mInscripcion de candidato descartado. No se guardo\033[0m"<<endl;
				}
                system("pause");
                break;
        case 2:
                system("cls");
                cout<<"***********************************************************"<<endl;
			    cout<<"               TABLA DE CANDIDATOS INSCRITOS               "<<endl;
			    cout<<"***********************************************************"<<endl;
				cout<<endl<<endl;
				cout<<"#CAN\tNombre Completo del Candidato\tPartido Politico\n";
                cout<<"-----------------------------------------------------------------\n";
				for(int i=0;i<n;i++){
					cout<<i+1<<" \t"<<User[i].nomCompleto<<"\t"<<User[i].PartidoPo<<endl;
				}
                cout<<endl;
				cout<<"Inserte el numero de orden del candidato a modificar:   "; cin>>opcion;
                cand = (opcion-1);
				//Casos en menu de opciones con do-while para poder volver al menu principal :D
                do{
					system("cls");
					cout<<"****************************************************"<<endl;
					cout<<"                 MENU DE MODIFICACIONES             "<<endl;
					cout<<"****************************************************"<<endl<<endl;
					cout<<"\tCandidato #"<<(cand+1)<<endl;
					cout<<"Nombre:           "<<User[cand].nomCompleto<<endl;
					cout<<"Sexo:             "<<User[cand].sexo<<endl;
					cout<<"Partido politico: "<<User[cand].PartidoPo<<endl;
					cout<<"Edad:             "<<User[cand].edad<<endl;
					cout<<"DNI:              "<<User[cand].dni<<endl;
					cout<<"Lema:             "<<User[cand].lema<<endl;
					cout<<"Correo electronico:\t"<<User[cand].email.user<<"@"<<User[cand].email.dom<<endl<<endl;
					
					cout<<"1. Nombre del candidato"<<endl;
					cout<<"2. Sexo del candidato"<<endl;
					cout<<"3. Partido politico"<<endl;
					cout<<"4. Edad del candidato"<<endl;
					cout<<"5. DNI del candidato"<<endl;
					cout<<"6. Lema del candidato"<<endl;
					cout<<"7. Email del candidato"<<endl;
					cout<<"8. Volver al menu principal"<<endl<<endl;
					cout<<"Ingrese su opcion: "; cin>>opcion;
					switch (opcion){
						case 1:
							system("cls");
							cout<<"Inserte el nombre modificado del candidato:"<<endl;
							cin.ignore();
							cout<<"Nombre: "; getline(cin,User[cand].nomCompleto);
							break;							
						case 2:
							system("cls");
							cout<<"Inserte el sexo modificado del candidato:"<<endl;
							cout<<"Sexo (M|F): "; cin>>User[cand].sexo;
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
							cout<<"Edad: ";cin>>User[cand].edad;
							break;
						case 5:
							system("cls");
							cout<<"Inserte el DNI modificado del candidato:"<<endl;
							cout<<"DNI: "; cin>>User[cand].dni;
							break;
						case 6:
							system("cls");
							cout<<"Inserte el lema modificado del candidato:"<<endl;
							cin.ignore();
							cout<<"Lema: ";getline(cin,User[cand].lema);
							break;
						case 7:
							system("cls");
							cout<<"Ingrese el correo electronico modificado (Usuario@dominio): "<<endl;
							cout<<"\tUsuario del correo: "; cin>>User[cand].email.user;
							cout<<"\tDominio del correo: "; cin>>User[cand].email.dom;
							break;
						case 8:
							break;
						default:
							cout<<"ERROR: Opcion fuera de los parametros, INTENTE OTRA VEZ !!!"<<endl;
							system("pause");
							break;
					}
				} while (opcion != 8);
				break;
        case 3:
            break;
        case 4:

            break;
        case 5:
            break;
        case 6:
            int opc;
            do{
                system("cls");
                cout<<"****************************************************"<<endl;
                cout<<"               PROCESO DE ELECCIONES                "<<endl;
                cout<<"****************************************************"<<endl;
                cout<<"1. Mostrar lista de candidatos(aptos)"<<endl;
                cout<<"2. Asignacion de mesas de votacion"<<endl;
                cout<<"3. Iniciar eleccciones(Emitir votos) "<<endl;
                cout<<"4. Ver resumen por mesa(total de votos)"<<endl;
                cout<<"5. Regresar al menu principal"<<endl;
                cout<<"Ingrese su opcion: ";cin>>opc;
                switch(opc){
                    case 1:
                        system("cls");
                        cout<<"***********************************************************"<<endl;
                        cout<<"                   CANDIDATOS OFICIALES                    "<<endl;
                        cout<<"***********************************************************"<<endl;
                        cout<<endl<<endl;
                        cout<<"#\tNombre Completo del Candidato\tPartido Politico\n";
                        cout<<"-----------------------------------------------------------------\n";
                    case 2:
                        system("cls");
                        break;
                    case 3:
                        system("cls");
                        break;
                    case 4:
                        system("cls");
                    case 5:
                        cout << "Regresando al menu principal...\n";
                        break;
                    default:
                        cout<<"ERROR: Opcion fuera de rango, INTENTE OTRA VEZ !!!"<<endl;
                        system("pause");
                        break;               
                }
            }while(opc!=5);
            break;
        case 7:
            break;
        case 0:
            break;
        default:
            cout<<"Opcion no valida!"<<endl;
            system("pause");
            break;

    }
    }while(opcion!=0);

    return 0;
}
void LeerCandidato(Candidato &c, string n, char s, int e,string d,string p, string l,  Correo em){
    c.nomCompleto = n;
    c.sexo  = s;
    c.edad = e;
    c.dni= d;
    c.PartidoPo = p;
    c.lema = l;
    c.email = em;
}

void LeerCorreo(Correo &e, string u, string d){
    e.user = u;
    e.dom = d;
}
void ImprimeCandidato(Candidato &c){
    cout<<"Nombres:          "<<c.nomCompleto<<endl;
    cout<<"DNI:              "<<c.dni<<endl;  
    cout<<"Sexo:             "<<c.sexo<<endl;
    cout<<"Edad:             "<<c.edad<<endl;
    cout<<"Email:            "<<c.email.user<<"@"<<c.email.dom<<endl;
    cout<<"Partido Politico: "<<c.PartidoPo<<endl;
    cout<<"Lema:             "<<c.lema<<endl;
}

	

