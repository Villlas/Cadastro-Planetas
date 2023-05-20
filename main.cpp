#include <iostream>
#include <unistd.h>
#include "App/App.h"
#include "models/Planets.h"
#include "Menu/menu.h"

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
        if (choose == 6)
            break;
        switch (choose)
        {
        case 1:
            Planet newPlanet;
            readNewPlanet(&newPlanet);
            Append(planetas, newPlanet);
            break;
        case 2:
            cout << "!Em produção!" << endl;
            break;
        case 3:
            int temp;
            quickSort(planetas.begin, planetas.end);
            PrintList(planetas, PrintRemove, true);
            cin >> temp;
            Remove(planetas, temp);
            break;
        case 4:
            cout << "!Em produção!" << endl;
            break;
        case 5:
            system(SO);
            cout << "Deseja organizar\n[1]ordem Alfábetica\n[2]Por Código\n> ";
            readInterger(&choose);
            if (choose == 1)
                BubbleSort(planetas, comparePlanets);
            else
                quickSort(planetas.begin, planetas.end);
            system(SO);
            PrintList(planetas, printPlanet);
            cin >> choose;
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