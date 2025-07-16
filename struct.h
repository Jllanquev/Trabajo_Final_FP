#ifndef ESTRUCT_H
#define ESTRUCT_H

#include <string>
#include <vector>
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

#endif