#include "generadorAleatorio.h"
#include "constantes.h"
#include <random>
#include <unordered_set>

using namespace std;


int generarDNI(){
     static mt19937 rng( random_device{}() );
     uniform_int_distribution<int> dist(40'000'000, 70'000'000);
     int d;
    do {
        d = dist(rng);                       // Genera un numero en el rango
    } while ( dnisUsados.count(d) );         // Repite si ya fue usado
    dnisUsados.insert(d);                    // Marca el DNI como usado
    return d;                                // Devuelve el DNI Unico
}

string generarDistrito(){
    int idx = rand() % NUM_DIST;
    return distritos[idx];
}

string generarNombre(){
    int idxNombre = rand() % NUM__NOMBRE;
    return nombre[idxNombre];
}

string generarApellido(){
    int idxApellido = rand() % NUM_APELLIDOS;
    return apellido[idxApellido];
}
