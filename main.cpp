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
        banner();
        showMenu();
        cout << "> ";
        readInterger(&choose);
        if (choose == 7)
            break;
        switch (choose)
        {
        case 1:
            Planet newPlanet;
            system(SO);
            readNewPlanet(&newPlanet);
            Append(planetas, newPlanet);
            cout << newPlanet.Name << " Adcionado com sucesso";
            exitMod();
            break;
        case 2:
            system(SO);
            changePlanet(planetas);
            exitMod();
            break;
        case 3:
            system(SO);
            removePlanet(planetas);
            cout << " Removido com sucesso" << endl;
            exitMod();
            break;
        case 4:
            searchPlanet(planetas, SO);
            cin.ignore();
            exitMod();
            break;
        case 5:
            system(SO);
            showOnePlanet(planetas);
            exitMod();
            break;
        case 6:
            system(SO);
            showAllPlanets(planetas, SO);
            exitMod();
            break;

        default:
            cout << "Valor inexistente" << endl;
            break;
        }
    }
    writePlanets(planetas);
    CleanMemory(planetas);
    return 0;
}