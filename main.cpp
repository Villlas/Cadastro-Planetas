#include <iostream>
#include "App/App.h"
#include "models/Planets.h"

using namespace std;

int main()
{
    int n;
    list<Planet> planetas;
    readPlanets(planetas);
    cout << "Como deseja organizar?\n[1]Alfabética(BubbleSort)\n[2]Codigo(QuickSort)" << endl;
    cin >> n;
    if (n == 1)
        BubbleSort(planetas, comparePlanets);
    if (n == 2)
        quickSort(planetas.begin, planetas.end);
    PrintList(planetas, printPlanet);
    cout << "Como deseja organizar?\n[1]Alfabética(BubbleSort)\n[2]Codigo(QuickSort)" << endl;
    cin >> n;
    if (n == 1)
        BubbleSort(planetas, comparePlanets);
    if (n == 2)
        quickSort(planetas.begin, planetas.end);
    PrintList(planetas, printPlanet);
    CleanMemory(planetas);
    return 0;
}