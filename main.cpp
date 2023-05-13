#include <iostream>
#include "src/App/app.h"
#include "src/Models/planets.h"

using namespace std;

int main()
{
    list<Planet> planetas;
    readPlanets(planetas);
    PrintList(planetas, printPlanet);
    CleanMemory(planetas);
    return 0;
}