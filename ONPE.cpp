#include<iostream>  
#include<string>   //para usar getline
#include<cstdio>
#include<random>     //para votar datos aleatorios
#include <unordered_set>  //para usar random
#include<cstdlib>    //para usar random
#include<ctime>     //para usar random
#include <iomanip>  //para mejorar la anchura de cada tabla
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
    int cand_voto;
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
const int NUM__NOMBRE = 50;  //nunca cambiara
string nombre[NUM__NOMBRE] = {
    "Juan", "Maria", "Luis", "Ana", "Pedro", "Carmen", "Jose", "Lucia", "Carlos", "Rosa",
    "Miguel", "Elena", "Jorge", "Sofia", "Ricardo", "Laura", "Daniel", "Patricia", "Alejandro", "Teresa",
    "Diego", "Gabriela", "Manuel", "Valeria", "Kevin", "Tatiana", "Raul", "Camila", "Sebastian", "Monica",
    "Bruno", "Noelia", "Axel", "Milagros", "Cristian", "Paola", "Renzo", "Estefany", "Bianca", "Oscar",
    "Fernando", "Ximena", "Gustavo", "Pilar", "Alan", "Antonia", "Nicolas", "Diana", "Santiago", "Isabela"
};
const int NUM_APELLIDOS = 50; //nunca cambiara
string apellido[NUM_APELLIDOS] = {
     "Perez", "Lopez", "Garcia", "Torres", "Diaz", "Rojas", "Vargas", "Fernandez", "Aguilar", "Salas",
    "Mendoza", "Castillo", "Herrera", "Flores", "Ramos", "Ruiz", "Soto", "Chavez", "Romero", "Navarro",
    "Llanque", "Bravo", "Salazar", "Vega", "Medina", "Palomino", "Paredes", "Silva", "Palacios", "Cabrera",
    "Rivera", "Calderon", "Mora", "Puma", "Delgado", "Acosta", "Lozano", "Valdivia", "Huaman", "Ortiz",
    "Limachi", "Espinoza", "Meza", "Cornejo", "Velasquez", "Vilca", "Aliaga", "Zevallos", "Huanca", "Quispe"
};

void LeerCorreo(Correo &, string, string);  //Leera el correo
void LeerCandidato(Candidato &,string,char,int,string,string,string,Correo);  //Leera los datos del candidato
void ImprimeCandidato(Candidato &);
void crearVotante(Votante &);
int generarDNI();
void buscarVotantePorDNI(int,Votante[], int,const vector<MesaDeVotacion>&);
string generarDistrito();
string generarNombre();
string generarApellido();

int main(){
    int opcion,cand,edad,n=0,max_votantes=1000,max_mesas=100000,cap,r[n],vot_distr=0,totalEmitidos;
	string partido,nombre,user,dom,dni,lema,distrito,OPC;
    char sexo;
    bool PadronVotantes = false,procesocerrado=false;
	Candidato User[200], InfoCand;
	Correo email;
    vector<MesaDeVotacion> mesas;
    srand(static_cast<unsigned int>(time(nullptr)));
    do{
    system("cls");
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
			system("cls");
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
            		Candidato &c=User[n];
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
             	    n++;
             	    cout << "\033[32mLa inscripcion ha sido exitosa\033[0m" << endl;
            	    cout<<endl;
				}
				else{
					cout<<"\033[31mInscripcion de candidato descartado. No se guardo\033[0m"<<endl;
				}
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
					cout<<left<<setw(8)<<i+1<<setw(32)<<User[i].Nombre<<User[i].PartidoPo<<endl;
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
        		//se va a evaluar el estado:
        		if(User[cand].Nombre.empty()||User[cand].PartidoPo.empty()||User[cand].Dni.empty()||User[cand].Lema.empty()){   // empty() verifica si el candidato se salto algo del registro 
        			User[cand].estado= PENDIENTE;
				}
				else if(User[cand].Edad<35){
					User[cand].estado= OBSERVADO;
				}
				else{
					User[cand].estado= APTO;
				} 
				break;
        case 3:
        	system("cls");
			cout<<"*****************************************************"<<endl;
			cout<<"                   LISTA DE CANDIDATOS               "<<endl;
			cout<<"*****************************************************"<<endl<<endl;

			for( int i = 0 ; i < n ; i++ ){
				cout<<"             CANDIDATO #"<<(i+1)<<":"<<endl;
				cout<<"Nombre:               "<<User[i].Nombre<<endl;
				cout<<"Sexo:                 "<<User[i].Sexo<<endl;
				cout<<"Partido politico:     "<<User[i].PartidoPo<<endl;
				cout<<"Edad:                 "<<User[i].Edad<<endl;
				cout<<"DNI:                  "<<User[i].Dni<<endl;
				cout<<"Lema:                 "<<User[i].Lema<<endl;
				cout<<"Correo electronico:   "<<User[i].Email.user<<"@"<<User[i].Email.dom<<endl<<endl;
			}
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
	            	cout << "Estimado(a) " << c.Nombre << ", su inscripcion ha sido OBSERVADA.\n";
	            	cout << "   Por favor revise sus datos para continuar en el proceso.\033[0m\n";
      			}
        	
        		
			}
			cout << "---------------------------------------------------------------------------------------------\n";

            break;
        case 5:
            system("cls");
            cout<<"CANDIDATOS: "<<endl<<endl;
			for(int i = 0; i < n; i++){
				cout << "Candidato #" << i + 1 << " - " << User[i].Nombre<< endl;
			}
			cout << "Ingrese el numero del candidato a eliminar: ";
            int mod;
			cin >> mod;
			mod--;
			if(mod >= 0 && mod < n){

                cout<<"?Estas seguro de eliminar este candidato?   ([S]Si|[N]No)  :";

                cin>>OPC;
                    if(OPC=="S"||OPC=="s"){   
                        for(int i = mod; i < n - 1; i++){
                            User[i] = User[i + 1];  
                        }
                        n--; // actualiza la cantidad de candidatos
                        cout << "\033[31mCandidato eliminado correctamente\033[0m\n";
                }
                else{
                    cout<<"Operacion cancelada.\n ";
                }
			} 
            else {
				cout << "Candidato no existente.\n";
			}
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
                cout<<"4. Buscar votante por DNI"<<endl;
                cout<<"5. Iniciar eleccciones(Emitir votos) "<<endl;
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
                        for (int i = 0 ; i < n ; i++ ){
                            if (User[i].estado == APTO){
                                cout<<left<<setw(8)<<"#"<<i+1<<setw(32)<<User[i].Nombre<<User[i].PartidoPo<<endl;
                            }
                        }
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        cout<<"***********************************************************"<<endl;
                        cout<<"                  ASIGNACION DE VOTANTES                   "<<endl;
                        cout<<"***********************************************************"<<endl;
                        if (!PadronVotantes) {
                                cout<<"Total de votantes que se crearan: "<< max_votantes <<endl;
                                nVotantes = 0;
                                dnisUsados.clear();
                                for (int i = 0; i < max_votantes && nVotantes < MAX_VOTANTES; ++i) {
                                    crearVotante(votantes[nVotantes]);
                                    nVotantes++;
                                }
                                PadronVotantes = true;
                                cout << "\n\033[32mPadron generado exitosamente.\033[0m\n";
                            } else {
                                cout << "\033[33mEl padron ya a sido generado.\033[0m\n";
                            }
                        cout<<endl;
                        system("pause");
                        system("cls");
                        cout<<"***********************************************************"<<endl;
                        cout<<"                     LISTA DE VOTANTES                     "<<endl;
                        cout<<"***********************************************************"<<endl; 
                        cout<<left << setw(8)<<"#"<<left << setw(15)<<"DNI votante"<<left << setw(30)<<"Nombre Completo del votante\tDistrito\n";
                        cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                        for(int i=0;i<nVotantes;i++){
                            cout<<left << setw(8)<<i+1<<left << setw(15)<< votantes[i].dni <<left << setw(30)<< votantes[i].nombre<<"\t"<<votantes[i].distrito << '\n';
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
                        cout<<"***********************************************************"<<endl;
                        cout<<"                    BUSCAR VOTANTE POR DNI                 "<<endl;
                        cout<<"***********************************************************"<<endl;
                        int dniBuscado;
                        cout<<"Ingrese el DNI del votante: ";cin>>dniBuscado;
                            buscarVotantePorDNI(dniBuscado, votantes, nVotantes, mesas);
                        cout<<"\nPresione ENTER para continuar...";  cin.ignore(); cin.get();
                        break;
                    case 5:
                        int opc1;
                        do {
                            system("cls");
                            cout<< "****************************************************" << endl;
                            cout<< "        \033[34mPROCESO DE VOTACION\033[0m          " << endl;
                            cout<< "****************************************************" << endl;
                            cout<< "1. Emitir voto manual (votante)" << endl;
                            cout<< "2. Ver avance de las votaciones "<<endl;
                            cout<< "3. Votacion automatica (simular 1 000 votos)" << endl;
                            cout<< "4. Culminar proceso de votacion" << endl;
                            cout<< "0. Regresar al menu principal" << endl;
                            cout<< "----------------------------------------------------" << endl;
                            cout<< "Ingrese su opcion: ";
                            cin>> opc1;

                            switch (opc1) {
                                case 1:{
                                    system("cls");
                                    if (procesocerrado) {
                                        cout << ">> El proceso ya fue cerrado. No se pueden emitir mas votos.\n";
                                        system("pause");
                                        break;
                                    }
                                    // Inicio del flujo de voto
                                    cout << "****************************************************" << endl;
                                    cout << "            \033[34mEMITIR VOTO\033[0m              " << endl;
                                    cout << "****************************************************" << endl;
                                    cout << "Ingrese su DNI: ";
                                    int dni;
                                    cin >> dni;
                                    // Buscar al votante
                                    int idx = -1;
                                    for (int i = 0; i < nVotantes; ++i) {
                                        if (votantes[i].dni == dni) {
                                            idx = i;
                                            break;
                                        }
                                    }
                                    if (idx == -1) {
                                        cout << "DNI no encontrado en el padr�n.\n";
                                        system("pause");
                                        break;
                                    }
                                    if (votantes[idx].haVotado) {
                                        cout << "Usted ya emitio su voto.\n";
                                        system("pause");
                                        break;
                                    }
                                    cout << "****************************************************" << endl;
                                    cout << "          \033[34mCEDULA DE SUFRAGIO\033[0m          " << endl;
                                    cout << "****************************************************" << endl;
                                    cout << "\tDatos Generales\n";
                                    cout << "---------------------------------------------------\n";
                                    cout << "Nombre:   " << votantes[idx].nombre << '\n';
                                    cout << "Edad:     " << votantes[idx].edad << '\n';
                                    cout << "Distrito: " << votantes[idx].distrito << "\n\n";

                                    char conf;
                                    cout << "Son correctos los datos? (S/N): ";
                                    cin >> conf;
                                    if (conf != 'S' && conf != 's') {
                                        cout << "Identidad no confirmada.\n";
                                        system("pause");
                                        break;
                                    }

                                    cout << "\n\t  VOTAR\n";
                                    cout << "-----------------------------------------------\n";
                                    int opcionVoto = 0;
                                    int numEnCedula = 0;
                                    int IndiceCand[200];  // Indice del Candidato
                                    for (int c = 0; c < n; ++c) {
                                        if (User[c].estado == APTO) {
                                            IndiceCand[++numEnCedula] = c;
                                            cout << setw(3) << numEnCedula << ". " << User[c].Nombre
                                                << "  (" << User[c].PartidoPo << ")\n";
                                        }
                                    }

                                    if (numEnCedula == 0) {
                                        cout << "\nNo hay candidatos aptos. Votacion cancelada.\n";
                                        system("pause");
                                        break;
                                    }
                                    // Voto
                                    cout << "\nMarque su voto (numero de candidato): ";
                                    cin >> opcionVoto;
                                    if (opcionVoto < 1 || opcionVoto > numEnCedula) {
                                        cout << "\nVoto invalido. Se contabilizara como nulo.\n";
                                    } else {
                                        int idxCand = IndiceCand[opcionVoto];
                                        User[idxCand].votos++;
                                        votantes[idx].cand_voto = idxCand;
                                        cout << "\n\033[32mVoto registrado correctamente.\033[0m\n";
                                    }
                                    votantes[idx].haVotado = true;
                                    // Incrementar votos en la mesa asignada
                                    for (size_t i = 0; i < mesas.size(); ++i) {
                                        if (mesas[i].numMesa == votantes[idx].n_mesa) {
                                            mesas[i].votosEmitidos++;
                                            break;
                                        }
                                    }
                                    system("pause");
                                    break;
                                }
                                case 2:{
                                        system("cls");
                                        //Calcular total de votos emitidos (solo candidatos APTO)
                                        totalEmitidos = 0;
                                        for (int c = 0; c < n; ++c)               // n = total de candidatos
                                            if (User[c].estado == APTO)
                                                totalEmitidos += User[c].votos;

                                        cout << "****************************************************" << endl;
                                        cout << "          \033[34mAVANCE DE LA VOTACION\033[0m      " << endl;
                                        cout << "****************************************************" << endl;
                                        cout << left<< setw(4)  << "#" << setw(25) << "Candidato"<< setw(12) << "Partido"<< setw(10) << "Votos"<< "%\n";
                                        cout << string(65,'-') << '\n';
                                        //Imprimir cada candidato apto con su porcentaje
                                        int orden = 0;
                                        for (int i = 0; i < n; ++i) {
                                            if (User[i].estado != APTO) continue;

                                            double pct = (totalEmitidos == 0)
                                                        ? 0.0
                                                        : 100.0 * User[i].votos / totalEmitidos;

                                            cout << left<< setw(4)  << ++orden<< setw(25) << User[i].Nombre.substr(0,24)<< setw(12) 
                                            << User[i].PartidoPo<< setw(10) << User[i].votos<< fixed << setprecision(1) << pct << "%\n";
                                        }
                                        //Linea final con el total de votos emitidos
                                        cout << string(65,'-') << '\n';
                                        cout << left << setw(41) << "TOTAL VOTOS EMITIDOS"
                                            << totalEmitidos << '\n';
                                        system("pause");
                                        break;
                                    }
                                    break;
                                case 3:{
                                    system("cls");
                                    if (procesocerrado) {
                                        cout << ">> El proceso ya fue cerrado. No se pueden emitir mas votos.\n";
                                        system("pause");
                                        break;
                                    }

                                    // Lista de indices de candidatos aptos
                                    vector<int> candidatosAptos;
                                    for (int i = 0; i < n; ++i)
                                        if (User[i].estado == APTO)
                                            candidatosAptos.push_back(i);

                                    if (candidatosAptos.empty()) {
                                        cout << "No hay candidatos aptos para recibir votos.\n";
                                        system("pause");
                                        break;
                                    }

                                    // Contador de votos emitidos
                                    int votosAuto = 0;

                                    // Simulacion
                                    for (int i = 0; i < nVotantes && votosAuto < 100000; ++i) {
                                        if (!votantes[i].haVotado) {
                                            // Elegir un candidato apto al azar
                                            int idxCandidato = candidatosAptos[rand() % candidatosAptos.size()];
                                            votantes[i].cand_voto = idxCandidato;
                                            User[idxCandidato].votos++;

                                            // Marcar como que voto
                                            votantes[i].haVotado = true;
                                            // Registrar voto en su mesa
                                            for (int j = 0; j < mesas.size(); ++j) {
                                                if (mesas[j].numMesa == votantes[i].n_mesa) {
                                                    mesas[j].votosEmitidos++;
                                                    break;
                                                }
                                            }

                                            votosAuto++;
                                        }
                                    }

                                    cout << "\n\033[32m>> Se emitieron " << votosAuto << " votos automaticamente.\033[0m\n";
                                    system("pause");
                                    break;
                                }   
                                case 4:{
                                    system("cls");
                                    if (procesocerrado) {
                                        cout << "\033[33m>> El proceso de votacion ya esta cerrado.\033[0m\n";
                                        system("pause");
                                        break;
                                    }

                                    cout << "****************************************************\n";
                                    cout << "        \033[34mCULMINAR PROCESO DE VOTACION\033[0m       \n";
                                    cout << "****************************************************\n";
                                    cout << "Desea finalizar las elecciones?\n";
                                    cout << "[S]SI  /   [N]No : ";
                                    char resp;
                                    cin >> resp;

                                    if (resp == 'S' || resp == 's') {
                                        procesocerrado = true;
                                        cout << "\n\033[32m>> Proceso de votacion cerrado exitosamente.\033[0m\n";
                                        cout << "   Ya no se podran emitir mas votos.\n";
                                    } else {
                                        cout << "\nOperacion cancelada. El proceso sigue abierto.\n";
                                    }

                                    system("pause");
                                    break;
                                }
                                case 0:
                                    cout << "\n\033[33mRegresando al menu principal...\033[0m\n";
                                    system("pause");
                                    break;

                                default:
                                    cout << "\033[31mOpcion invalida. Intente de nuevo.\033[0m\n";
                                    system("pause");
                                    break;
                            }
                        } while (opc1 != 0);
                        break;
                    case 6:
                        cout << "Regresando al menu principal...\n";
                        break;
                    default:
                        cout<<"ERROR: Opcion fuera de rango, INTENTE OTRA VEZ !!!"<<endl;
                        system("pause");
                        break;               
                }
            }while(opt!=6);
            break;
        case 7:
            system("cls");
            cout<<"************************************************************************************"<<endl;
            cout<<"                                     RESULTADOS                                     "<<endl;
            cout<<"************************************************************************************"<<endl<<endl;
            for (int i = 0; i < n; i++){
                r[i]=User[i].votos;
            }
            for (int i = 0; i < n ; i++){
                for (int j = 0; j < n - i -1; j++){
                    if(r[j] < r[j+1]){
                        int temp = r[j];
                        r[j] = r[j+1];
                        r[j+1] = temp;
                    }
                }
            }
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (r[i] == User[j].votos){

                        float por; //Para hallar el porcentaje de votos
                        por = User[j].votos * (100.00 / totalEmitidos);

                        cout<<left<<i+1<<".-"<<setw(30)<<User[j].Nombre<<setw(20)<<User[j].PartidoPo
                        <<setw(20)<<User[j].Lema<<setw(5)<<User[j].votos<<setw(9)<<" votos"<<setw(5)
                        <<por<<"%"<<endl;
                    }
                }
            }

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
    v.nombre    = generarNombre() + " " + generarApellido() + " " + generarApellido();
    v.n_mesa    = -1;
    v.haVotado  = false;
}

int generarDNI(){
     static mt19937 rng( random_device{}() );
     uniform_int_distribution<int> dist(40'000'000, 70'000'000);
     int d;
    do {
        d = dist(rng);                       // Genera un numero en el rango
    } while ( dnisUsados.count(d) );         // Repite si ya fue usado
    dnisUsados.insert(d);                    // Marca el DNI como usado
    return d;                                // Devuelve el DNI Unico
}
string generarDistrito(){
    int idx = rand() % NUM_DIST;
    return distritos[idx];
}
string generarNombre(){
    int idxNombre = rand() % NUM__NOMBRE;
    return nombre[idxNombre];
}
string generarApellido(){
    int idxApellido = rand() % NUM_APELLIDOS;
    return apellido[idxApellido];
}
void buscarVotantePorDNI(int dniBuscado,Votante votantes[], int nVotantes,const vector<MesaDeVotacion>& mesas){
    bool encontrado = false; 
    for(int i=0;i<nVotantes;i++){
        if(votantes[i].dni==dniBuscado){
            encontrado = true;
            cout << "\n\033[36mVOTANTE ENCONTRADO\033[0m\n";
            cout << "DNI:        " << votantes[i].dni      << '\n';
            cout << "Nombre:     " << votantes[i].nombre   << '\n';
            cout << "Distrito:   " << votantes[i].distrito << '\n';
            cout << "Ha votado:  " << (votantes[i].haVotado ? "Si" : "No") << '\n';
            if (votantes[i].n_mesa == -1) {
            cout << "\n\033[31mAun no tiene mesa asignada\033[0m" << endl;
            }
            else {
                for (size_t j = 0; j < mesas.size(); ++j) {
                    if (mesas[j].numMesa == votantes[i].n_mesa) {
                        cout << "\n\033[36mMESA DE VOTACION\033[0m\n";
                        cout << "N Mesa:   " << mesas[j].numMesa       << endl;
                        cout << "Distrito:  " << mesas[j].distrito      << endl;
                        break;  
                    }
                }
            }
            break;  
        }
    }
    if(!encontrado)
        cout<<"\n\t\033[31mVOTANTE NO ENCONTRADO\033[0m\n";
    return;
};
