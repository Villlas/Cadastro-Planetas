#include <iostream>
#include <unistd.h>
#include "App/App.h"
#include "models/Planets.h"
#include "Interface/menu.h"

using namespace std;

int main()
{
    list<Planet> planetas;
    int soChoose;
    int choose;
    readPlanets(planetas);

    cout << "Qual o seu sistema operacional\n[1]Windows\n[2]Linux/Mac\n>";
    char SO[10];
    while (true)
    {
        readInterger(&soChoose);
        if (soChoose == 1 || soChoose == 2)
        {
            (soChoose != 2) ? strcpy(SO, "cls") : strcpy(SO, "clear");
            break;
        }
        cout << "Valores inválidos" << endl;
    }

    while (true)
    {
        system(SO);
        showMenu();
        cout << "> ";
        readInterger(&choose);
        if (choose == 7)
            break;
        switch (choose)
        {
        case 1:
            Planet newPlanet;
            readNewPlanet(&newPlanet);
            Append(planetas, newPlanet);
            break;
        case 2:
            changePlanet(planetas);
            break;
        case 3:
            removePlanet(planetas);
            break;
        case 4:
            // Busca Binária com dois elementos diferentes
            searchPlanet(planetas, SO);
            break;
        case 5:
            system(SO);
            showOnePlanet(planetas);
            cin >> choose;
            break;
        case 6:
            system(SO);
            showAllPlanets(planetas, SO);
            cin >> choose;
            break;

        default:
            cout << "Valor inexistente" << endl;
            break;
        }
    }

    quickSort(planetas.begin, planetas.end);
    writePlanets(planetas);
    CleanMemory(planetas);
    return 0;
}