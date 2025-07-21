#pragma once
#include <string>
#include <unordered_set>
using namespace std;

const int MAX_VOTANTES = 2000; //nunca cambiara
const int NUM_DIST = 11;  //nunca cambiara
const int NUM__NOMBRE = 50;  //nunca cambiara
const int NUM_APELLIDOS = 50; //nunca cambiara

extern int nVotantes;
extern unordered_set<int> dnisUsados;

extern const string distritos[NUM_DIST];
extern const string nombre[NUM__NOMBRE];
extern const string apellido[NUM_APELLIDOS];