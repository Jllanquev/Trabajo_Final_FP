#include "candidato.h"
#include<iostream>

using namespace std;

void LeerCandidato(Candidato &c, string n, char s, int e,string d,string p, string l,  Correo em){
    c.Nombre = n;
    c.Sexo  = s;
    c.Edad = e;
    c.Dni= d;
    c.PartidoPo = p;
    c.Lema = l;
    c.Email = em;
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

void EvaluarEstado(Candidato &c) {
    if (c.Nombre.empty() || c.PartidoPo.empty() || c.Dni.empty() || c.Lema.empty()) {
        c.estado = PENDIENTE;
    } else if (c.Edad < 35) {
        c.estado = OBSERVADO;
    } else {
        c.estado = APTO;
    }
}