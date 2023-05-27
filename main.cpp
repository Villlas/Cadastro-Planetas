#include <iostream>
#include "App/App.h"
#include "models/Planets.h"
#include "Interface/menu.h"

using namespace std;

int main()
{
    list<Planet> planetas;
    char SO[10];
    readPlanets(planetas);
    readSo(SO);
    init(planetas, SO);
    writePlanets(planetas);
    CleanMemory(planetas);
    return 0;
}