#include <iostream>
#include "App/App.h"
#include "models/Planets.h"


using namespace std;

int main()
{
    list<Planet> planetas;
    readPlanets(planetas);
    cout << planetas.count << endl;
    QuickSort(planetas, 0, planetas.count);
    CleanMemory(planetas);
    return 0;
}