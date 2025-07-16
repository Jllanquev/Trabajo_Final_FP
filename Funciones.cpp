#include "Funciones.h"
#include "globales.h"
#include <iostream>
#include <random>
using namespace std;

void LeerCandidato(Candidato &c, string n, char s, int e, string d, string p, string l, Correo em) {
    c.Nombre = n;
    c.Sexo = s;
    c.Edad = e;
    c.Dni = d;
    c.PartidoPo = p;
    c.Lema = l;
    c.Email = em;
}

void LeerCorreo(Correo &e, string u, string d) {
    e.user = u;
    e.dom = d;
}

void ImprimeCandidato(Candidato &c) {
    cout << "Nombres:          " << c.Nombre << endl;
    cout << "DNI:              " << c.Dni << endl;
    cout << "Sexo:             " << c.Sexo << endl;
    cout << "Edad:             " << c.Edad << endl;
    cout << "Email:            " << c.Email.user << "@" << c.Email.dom << endl;
    cout << "Partido Politico: " << c.PartidoPo << endl;
    cout << "Lema:             " << c.Lema << endl;
}

void crearVotante(Votante &v) {
    v.dni = generarDNI();
    v.distrito = generarDistrito();
    v.nombre = generarNombre() + " " + generarApellido() + " " + generarApellido();
    v.n_mesa = -1;
    v.haVotado = false;
}

int generarDNI() {
    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(40000000, 70000000);
    int d;
    do {
        d = dist(rng);
    } while (dnisUsados.count(d));
    dnisUsados.insert(d);
    return d;
}

string generarDistrito() {
    int idx = rand() % NUM_DIST;
    return distritos[idx];
}

string generarNombre() {
    int idxNombre = rand() % NUM__NOMBRE;
    return nombre[idxNombre];
}

string generarApellido() {
    int idxApellido = rand() % NUM_APELLIDOS;
    return apellido[idxApellido];
}

void buscarVotantePorDNI(int dniBuscado, Votante votantes[], int nVotantes, const vector<MesaDeVotacion>& mesas) {
    bool encontrado = false;
    for (int i = 0; i < nVotantes; i++) {
        if (votantes[i].dni == dniBuscado) {
            encontrado = true;
            cout << "\n\033[36mVOTANTE ENCONTRADO\033[0m\n";
            cout << "DNI:        " << votantes[i].dni << '\n';
            cout << "Nombre:     " << votantes[i].nombre << '\n';
            cout << "Distrito:   " << votantes[i].distrito << '\n';
            cout << "Ha votado:  " << (votantes[i].haVotado ? "Si" : "No") << '\n';
            if (votantes[i].n_mesa == -1) {
                cout << "\n\033[31mAun no tiene mesa asignada\033[0m" << endl;
            } else {
                for (const auto &mesa : mesas) {
                    if (mesa.numMesa == votantes[i].n_mesa) {
                        cout << "\n\033[36mMESA DE VOTACION\033[0m\n";
                        cout << "N Mesa:   " << mesa.numMesa << endl;
                        cout << "Distrito:  " << mesa.distrito << endl;
                        break;
                    }
                }
            }
            break;
        }
    }
    if (!encontrado)
        cout << "\n\t\033[31mVOTANTE NO ENCONTRADO\033[0m\n";
}
