#ifndef GLOBALES_H
#define GLOBALES_H
#define MAX_VOTANTES 2000

#include <set>
#include <string>
#include "struct.h"

extern set<int> dnisUsados;
extern Votante votantes[2000];
extern int nVotantes;

extern const int NUM_DIST;
extern const int NUM__NOMBRE;
extern const int NUM_APELLIDOS;

extern string distritos[11];
extern string nombre[50];
extern string apellido[50];

#endif