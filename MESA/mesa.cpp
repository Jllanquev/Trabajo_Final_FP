#include "mesa.h"
#include "constantes.h"
#include "votante.h"
#include<iostream>
#include <iomanip>

using namespace std;

void mostrarResumenDistritos(int cuenta[], const Votante votantes[], int nVotantes) {
    for (int i = 0; i < NUM_DIST; ++i) cuenta[i] = 0;

    for (int i = 0; i < nVotantes; i++) {
        for (int j = 0; j < NUM_DIST; j++) {
            if (votantes[i].distrito == distritos[j]) {
                cuenta[j]++;
                break;
            }
        }
    }
    cout << left << setw(28) << "Distrito" << "Votantes\n";
    cout << "------------------------------------------\n";
    for (int j = 0; j < NUM_DIST; j++) {
        cout << left << setw(28) << distritos[j] << "\t" << cuenta[j] << '\n';
    }
}

