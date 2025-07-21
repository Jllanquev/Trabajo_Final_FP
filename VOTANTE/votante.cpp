#include "votante.h"
#include "generadorAleatorio.h"
#include <iostream>

using namespace std;

void crearVotante(Votante &v) {
    v.dni       = generarDNI();
    v.distrito  = generarDistrito();
    v.nombre    = generarNombre() + " " + generarApellido() + " " + generarApellido();
    v.n_mesa    = -1;
    v.haVotado  = false;
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

