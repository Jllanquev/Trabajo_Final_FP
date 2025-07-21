#pragma once
#include "correo.h"

enum EstadoCandidato { PENDIENTE, APTO, OBSERVADO };

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

void LeerCandidato(Candidato &,string,char,int,string,string,string,Correo);  //Leera los datos del candidato
void ImprimeCandidato(Candidato &);
void EvaluarEstado(Candidato &);