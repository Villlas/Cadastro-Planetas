#include <iostream>
#define TAM_CHARS 100

using namespace std;

struct Planet
{
    u_int16_t Id;
    char Name[TAM_CHARS];
    char Type[TAM_CHARS];
    char Galaxy[TAM_CHARS];
};

void printPlanet(Planet planet) {
    cout << "-------------------------------" << endl;
    cout << "ID: "<< planet.Id << endl;
    cout << "Nome: "<< planet.Name << endl;
    cout << "Tipo: "<< planet.Type << endl;
    cout << "Galaxia pertencente: "<< planet.Galaxy << endl;
}
