#include "globales.h"

set<int> dnisUsados;
Votante votantes[2000];
int nVotantes = 0;

const int NUM_DIST = 11;
const int NUM__NOMBRE = 50;
const int NUM_APELLIDOS = 50;

string distritos[NUM_DIST] = { "Tacna", "Alto de la Alianza", "Calana", "Ciudad Nueva",
    "Gregorio Albarracin", "Inclan", "La Yarada-Los Palos", "Pachia", "Palca", "Pocollay", "Sama" };

string nombre[NUM__NOMBRE] = { "Juan", "Maria", "Luis", "Ana", "Pedro", "Carmen", "Jose", "Lucia", "Carlos", "Rosa",
    "Miguel", "Elena", "Jorge", "Sofia", "Ricardo", "Laura", "Daniel", "Patricia", "Alejandro", "Teresa",
    "Diego", "Gabriela", "Manuel", "Valeria", "Kevin", "Tatiana", "Raul", "Camila", "Sebastian", "Monica",
    "Bruno", "Noelia", "Axel", "Milagros", "Cristian", "Paola", "Renzo", "Estefany", "Bianca", "Oscar",
    "Fernando", "Ximena", "Gustavo", "Pilar", "Alan", "Antonia", "Nicolas", "Diana", "Santiago", "Isabela" };

string apellido[NUM_APELLIDOS] = { "Perez", "Lopez", "Garcia", "Torres", "Diaz", "Rojas", "Vargas", "Fernandez", "Aguilar", "Salas",
    "Mendoza", "Castillo", "Herrera", "Flores", "Ramos", "Ruiz", "Soto", "Chavez", "Romero", "Navarro",
    "Llanque", "Bravo", "Salazar", "Vega", "Medina", "Palomino", "Paredes", "Silva", "Palacios", "Cabrera",
    "Rivera", "Calderon", "Mora", "Puma", "Delgado", "Acosta", "Lozano", "Valdivia", "Huaman", "Ortiz",
    "Limachi", "Espinoza", "Meza", "Cornejo", "Velasquez", "Vilca", "Aliaga", "Zevallos", "Huanca", "Quispe" };
