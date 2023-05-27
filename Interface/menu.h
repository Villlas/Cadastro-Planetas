#include <iostream>
#include <string>

using namespace std;

#define TAM_OPTIONS 7
#define TAM_MAX 100

char options[TAM_OPTIONS][TAM_MAX] =
    {
        "[1] Adcionar um novo planeta",
        "[2] Alterar dados de um planeta",
        "[3] Remover um planeta",
        "[4] Buscar um planeta",
        "[5] Mostrar dados de um planeta",
        "[6] Mostrar planetas",
        "[7] Sair do sistema"};
void banner()
{
    cout << "===============================" << endl;
    cout << "  Agencia Espacial Brasileira  " << endl;
    cout << "===============================" << endl;
}

void showMenu()
{
    for (int i = 0; i < TAM_OPTIONS; i++)
        cout << options[i] << endl;
}

void readInterger(int *value)
{
    while (!(cin >> *value))
    {
        cout << "Digite um valor inteiro valido!\n> ";
        cin.clear();
        cin.ignore(123, '\n');
    }
}

void exitMod()
{
    cout << "\nTecle ENTER para voltar ao menu...";
    cin.get();
}

void readSo(char *SO)
{
    int soChoose;
    cout << "Qual o seu sistema operacional\n[1]Windows\n[2]Linux/Mac\n>";
    while (true)
    {
        readInterger(&soChoose);
        if (soChoose == 1 || soChoose == 2)
        {
            (soChoose != 2) ? strcpy(SO, "cls") : strcpy(SO, "clear");
            return;
        }
        cout << "Valores inválidos" << endl;
    }

}

void init(list<Planet> &planetas, char *SO)
{
    int choose;
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
}