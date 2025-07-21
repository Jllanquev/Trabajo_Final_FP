#pragma once
#include <string>
#include <vector>
#include "constantes.h"
#include "../MESA/mesa.h"
using namespace std;

struct Votante {
    int dni;
    string nombre;
    string distrito;
    int edad;
    int n_mesa;         
    bool haVotado = false;
    int cand_voto;
};

void crearVotante(Votante &);
void buscarVotantePorDNI(int,Votante[], int,const vector<MesaDeVotacion>&);