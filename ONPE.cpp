#include<iostream>
#include<string>
#include<cstdio>
#include<random>
#include <unordered_set>
#include<cstdlib>
#include<ctime>
#include <iomanip>
#include<vector>

using namespace std;

enum EstadoCandidato { PENDIENTE, APTO, OBSERVADO };

struct Correo {
    string user;
    string dom;
};

struct Candidato {
    int numero;               
    string Nombre;
    char Sexo;
    int Edad;
    string Dni;
    Correo Email;
    string PartidoPo;
    string Lema;
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
    int dni;
    string nombre;
    string distrito;
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
unordered_set<int> dnisUsados; 
//Para definir al votante
const int MAX_VOTANTES = 2000; //nunca cambiara
Votante votantes[MAX_VOTANTES];
int nVotantes = 0; //votantes registrados

//Para definir el distrito de cada votante
const int NUM_DIST = 11;  //nunca cambiara
string distritos[NUM_DIST] = {
    "Tacna","Alto de la Alianza","Calana","Ciudad Nueva",
    "Gregorio Albarracin","Inclan","La Yarada-Los Palos",
    "Pachia","Palca","Pocollay","Sama"
};
void LeerCorreo(Correo &, string, string);  //Leera el correo
void LeerCandidato(Candidato &,string,char,int,string,string,string,Correo);  //Leera los datos del candidato
void ImprimeCandidato(Candidato &);
void crearVotante(Votante &);
int generarDNI();
string generarDistrito();
int main(){
    int opcion,cand,edad,n=0,max_votantes=1000,max_mesas=100000,cap;
	string partido,nombre,user,dom,dni,lema,distrito;
    char sexo;
	Candidato User[200], InfoCand;
	Correo email;
    vector<MesaDeVotacion> mesas;
    do{
     cout<<"*****************************************************"<<endl;
	cout<<"                  \033[31mONPE\033[0m                     "<<endl;
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
			cout<<"Dni: "; getline(cin,dni);
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
                system("cls");

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
					cout<<i+1<<" \t"<<User[i].Nombre<<"\t"<<User[i].PartidoPo<<endl;
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
					cout<<"Nombre:           "<<User[cand].Nombre<<endl;
					cout<<"Sexo:             "<<User[cand].Sexo<<endl;
					cout<<"Partido politico: "<<User[cand].PartidoPo<<endl;
					cout<<"Edad:             "<<User[cand].Edad<<endl;
					cout<<"DNI:              "<<User[cand].Dni<<endl;
					cout<<"Lema:             "<<User[cand].Lema<<endl;
					cout<<"Correo electronico:\t"<<User[cand].Email.user<<"@"<<User[cand].Email.dom<<endl<<endl;
					
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
							cout<<"\tDominio del correo: "; cin>>User[cand].Email.dom;
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
					cout<<"Correo electronico:\t"<<User[i].Email.user<<"@"<<User[i].Email.dom<<endl<<endl;
				}
				system("pause");
				system("cls");
            break;
        case 4:
        	system("cls");
        	//se va mostrar en la tabla:
         	cout<<"==================REVISION GENERAL DE CANDIDATOS===================\n\n"<<endl;
        	cout << "---------------------------------------------------------------------------------------------\n";
 		   	cout << "| # |      NOMBRE       |   DNI    | EDAD |         CORREO         |   ESTADO   |\n";
    		cout << "---------------------------------------------------------------------------------------------\n";  
    		
        	for(int i=0;i<n;i++){
        		Candidato &c=User[i];
        		//se va a evaluar el estado:
        		if(c.Nombre.empty()||c.PartidoPo.empty()||c.Dni.empty()||c.Lema.empty()){   // empty() verifica si el candidato se salto algo del registro 
        			c.estado= PENDIENTE;
				}
				else if(c.Edad<35){
					c.estado= OBSERVADO;
				}
				else{
					c.estado= APTO;
				}     		
        	
				//color y estado del texto:
				string color,estadotexto;
				switch(c.estado){
					case APTO: 
						color = "\033[32m"; estadotexto = "APTO     "; break;
		        	case OBSERVADO: 
						color = "\033[33m"; estadotexto = "OBSERVADO"; break;
		            case PENDIENTE: 
						color = "\033[31m"; estadotexto = "PENDIENTE"; break;	
				}
				
			    printf("| %2d | %-17s | %-8s | %4d | %-23s | %s%-10s\033[0m |\n",
			            i + 1,
			            c.Nombre.c_str(),
			            c.Dni.c_str(),
			            c.Edad,
			            (c.Email.user + "@" + c.Email.dom).c_str(),
			            color.c_str(),
			            estadotexto.c_str()
			        );	
			        
			    //Si el usuario es Observado se le enviara un correo
		        if (c.estado == OBSERVADO) {
	            	cout << "\033[33m>> Correo enviado a " << c.Email.user << "@" << c.Email.dom << ": ";
	            	cout << "Estimado(a) " << c.Nombre << ", su inscripción ha sido OBSERVADA.\n";
	            	cout << "   Por favor revise sus datos para continuar en el proceso.\033[0m\n";
      			}
        	
        		
			}
			cout << "---------------------------------------------------------------------------------------------\n";

        	system("pause");
        	system("cls");
            break;
        case 5:
            break;
        case 6:
            int opt;
            do{
                system("cls");
                cout<<"****************************************************"<<endl;
                cout<<"               PROCESO DE ELECCIONES                "<<endl;
                cout<<"****************************************************"<<endl;
                cout<<"1. Mostrar lista de candidatos(aptos)"<<endl;

                cout<<"2. Asignacion de votantes"<<endl;
                cout<<"3. Asignacion de mesas de votacion"<<endl;
                cout<<"4. Iniciar eleccciones(Emitir votos) "<<endl;
                cout<<"5. Ver resumen por mesa(total de votos)"<<endl;
                cout<<"6. Regresar al menu principal"<<endl;
                cout<<"Ingrese su opcion: ";cin>>opt;
                switch(opt){
                    case 1:
                        system("cls");
                        cout<<"***********************************************************"<<endl;
                        cout<<"                   CANDIDATOS OFICIALES                    "<<endl;
                        cout<<"***********************************************************"<<endl;
                        cout<<endl<<endl;
                        cout<<"#\tNombre Completo del Candidato\tPartido Politico\n";
                        cout<<"-----------------------------------------------------------------\n";

                        break;
                    case 2:
                        system("cls");
                        cout<<"***********************************************************"<<endl;
                        cout<<"                  ASIGNACION DE VOTANTES                   "<<endl;
                        cout<<"***********************************************************"<<endl;
                        cout<<"Total de votantes: "<<max_votantes;
                        for(int i=0;i<max_votantes && nVotantes < MAX_VOTANTES;i++){
                            crearVotante(votantes[nVotantes]);
                            nVotantes++;
                        }
                        cout<<endl;
                        system("cls");
                        cout<<"***********************************************************"<<endl;
                        cout<<"                     LISTA DE VOTANTES                     "<<endl;
                        cout<<"***********************************************************"<<endl; 
                        cout<<"#\tDNI votante\tDistrito\n";
                        cout<<"---------------------------------------------------------------"<<endl;
                        for(int i=0;i<nVotantes;i++){
                            cout<<i+1<<" \t"<< votantes[i].dni << '\t' << votantes[i].distrito << '\n';
                        }
                        cout<<"Presione ENTER para continuar..."; cin.ignore(); cin.get();
                        break;
                    case 3:{
                        system("cls");
                        cout<<"***********************************************************"<<endl;
                        cout<<"               ASIGNACION DE MESAS ELECTORALES             "<<endl;
                        cout<<"***********************************************************"<<endl;
                        cout<<"Resumen por distrito:"<<endl;
                        cout<<"--------------------------------------------"<<endl;
                        cout << left << setw(28)<<"Distrito"<<"Votantes\n";
                        cout << "------------------------------------------"<<endl;
                        int cuenta[NUM_DIST]={0};
                        for(int i=0; i<nVotantes;i++){
                            for(int j=0;j<NUM_DIST;j++){
                                if(votantes[i].distrito==distritos[j]){
                                    cuenta[j]++;
                                    break;
                                }
                            }
                        }
                        for(int j=0;j<NUM_DIST;j++){
                            cout << left << setw(28)<<distritos[j]<<" \t"<<cuenta[j]<<" \n";
                        }
                        cout<<endl;
                        cout<<"Total de votantes:                     "<<max_votantes<<endl;
                        cout<<"Ingrese la capacidad por cada mesa:    ";cin>>cap;     
                        int numMesa = 100001;
                        for (int j = 0; j < NUM_DIST; ++j) {
                            int mesasNecesarias = (cuenta[j] + cap - 1) / cap;
                            for (int m = 0; m < mesasNecesarias; ++m) {
                                MesaDeVotacion nueva;
                                nueva.numMesa   = numMesa++;
                                nueva.distrito  = distritos[j];
                                nueva.capacidad = cap;
                                nueva.votosEmitidos = 0;
                                mesas.push_back(nueva);
                            }
                        }
                        for (int i = 0; i < nVotantes; ++i) {
                            for (size_t j = 0; j < mesas.size(); j++) {
                                MesaDeVotacion &mesa = mesas[j];
                                if (mesa.distrito == votantes[i].distrito && mesa.votosEmitidos < mesa.capacidad) {
                                    mesa.dniAsig[mesa.votosEmitidos++] = votantes[i].dni;
                                    votantes[i].n_mesa = mesa.numMesa;
                                    break;
                                }
                            }
                        }
                        cout << "\nMESAS CREADAS\n";
                        cout << left << setw(8) << "Mesa"<< setw(28) << "Distrito" << setw(10) << "Cap."<< "Asignados\n";
                        cout<< "----------------------------------------------------------------------------------\n";
                        for (size_t i = 0; i < mesas.size(); ++i) {
                            cout << left << setw(8)  << mesas[i].numMesa<< setw(28) << mesas[i].distrito  << setw(10) 
                            << mesas[i].capacidad << mesas[i].votosEmitidos << '\n';
                        }

                        cout<<"Presione ENTER para continuar..."; cin.ignore(); cin.get();
                        break;
                    }
                    case 4:
                        system("cls");
                        break;
                    case 5:
                        system("cls"); 
                        break;
                    case 6:
                        cout << "Regresando al menu principal...\n";
                        break;
                    default:
                        cout<<"ERROR: Opcion fuera de rango, INTENTE OTRA VEZ !!!"<<endl;
                        system("pause");
                        break;               
                }
            }while(opt!=5);
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
    system("pause");
    }while(opcion!=0);
    return 0;
}
void LeerCandidato(Candidato &c, string n, char s, int e,string d,string p, string l,  Correo em){
    c.Nombre = n;
    c.Sexo  = s;
    c.Edad = e;
    c.Dni= d;
    c.PartidoPo = p;
    c.Lema = l;
    c.Email = em;
}

void LeerCorreo(Correo &e, string u, string d){
    e.user = u;
    e.dom = d;

}
void ImprimeCandidato(Candidato &c){
    cout<<"Nombres:          "<<c.Nombre<<endl;
    cout<<"DNI:              "<<c.Dni<<endl;  
    cout<<"Sexo:             "<<c.Sexo<<endl;
    cout<<"Edad:             "<<c.Edad<<endl;
    cout<<"Email:            "<<c.Email.user<<"@"<<c.Email.dom<<endl;
    cout<<"Partido Politico: "<<c.PartidoPo<<endl;
    cout<<"Lema:             "<<c.Lema<<endl;
}
void crearVotante(Votante &v) {
    v.dni       = generarDNI();
    v.distrito  = generarDistrito();
    v.n_mesa    = -1;
    v.haVotado  = false;
}

int generarDNI(){
     static mt19937 rng( random_device{}() );
     uniform_int_distribution<int> dist(40'000'000, 70'000'000);
     int d;
    do {
        d = dist(rng);                       // Genera un nÃºmero en el rango
    } while ( dnisUsados.count(d) );         // Repite si ya fue usado
    dnisUsados.insert(d);                    // Marca el DNI como usado
    return d;                                // Devuelve el DNI Ãºnico
}
string generarDistrito(){
    int idx = rand() % NUM_DIST;
    return distritos[idx];
}
