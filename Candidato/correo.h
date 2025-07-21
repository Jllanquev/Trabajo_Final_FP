#pragma once
#include<string>

using namespace std;

struct Correo {
    string user;
    string dom;
};
void LeerCorreo(Correo &, string, string);  //Leera el correo