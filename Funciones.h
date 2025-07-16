#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>
#include "struct.h"

void LeerCorreo(Correo &, string, string);
void LeerCandidato(Candidato &, string, char, int, string, string, string, Correo);
void ImprimeCandidato(Candidato &);
void crearVotante(Votante &);
int generarDNI();
string generarDistrito();
string generarNombre();
string generarApellido();
void buscarVotantePorDNI(int, Votante[], int, const vector<MesaDeVotacion>&);

#endif
