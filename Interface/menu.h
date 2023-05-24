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

void showMenu()
{
    for (int i = 0; i < TAM_OPTIONS; i++)
        cout << options[i] << endl;
}

void readInterger(int *value)
{
    while (!(cin >> *value))
    {
        cout << "Digite um valor inteiro válido!\n> ";
        cin.clear();
        cin.ignore(123, '\n');
    }
}

void exitMod()
{
    cin.ignore();
    cout << "Tecle ENTER para sair...";
    cin.get();
}