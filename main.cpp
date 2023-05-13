#include <iostream>
#include "src/App/app.h"
#include "src/Menu/menu.h"
#include "src/Planets/planets.h"

using namespace std;

int main()
{
    list<Planet> planetas;
    Append(planetas, {1, "Marte", "Rochoso", "Via Láctea"});
    Append(planetas, {2, "Urano", "Gasoso", "Via Láctea"});
    PrintList(planetas, printPlanet);
    CleanMemory(planetas);
    return 0;
}