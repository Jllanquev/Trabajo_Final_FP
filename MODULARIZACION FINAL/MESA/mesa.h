#pragma once
#include <string>
#include <vector>

using namespace std;
class Votante;
struct MesaDeVotacion {
    int numMesa;                 
    string distrito;               
    int dniAsig[500];
    int votosEmitidos = 0;          
    int capacidad = 500;             
};

void mostrarResumenDistritos(int[], const Votante [], int );
