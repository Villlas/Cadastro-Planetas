#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

#define TAM 100
#define LOCAL "Data/dataBase.csv"

struct Planet
{
    int Code;
    char Name[TAM];
    char Type[TAM];
    char Galaxy[TAM];
};

void printPlanet(const Planet planet)
{
    cout << "-------------------------------" << endl;
    cout << "Código: " << planet.Code << endl;
    cout << "Nome: " << planet.Name << endl;
    cout << "Tipo: " << planet.Type << endl;
    cout << "Galaxia pertencente: " << planet.Galaxy;
}

void PrintRemove(const Planet planet)
{
    cout << planet.Name << endl;
}
int searchChar(char letter, int posi, char *line)
{
    int atual = posi;
    while (line[atual] != letter)
        atual++;
    return atual;
}

void readPlanets(list<Planet> &lst)
{
    FILE *fptr;

    fptr = fopen(LOCAL, "r");

    if (fptr == NULL)
    {
        cout << "Not able to open the file." << endl;
        fclose(fptr);
        return;
    }

    char str[TAM];
    while (fgets(str, TAM, fptr))
    {
        Planet atual;
        char temp[TAM];

        // Copiando o id
        memset(temp, 0, TAM);
        int pos = searchChar(';', 0, str);
        strncpy(temp, str, pos);
        atual.Code = atoi(temp);

        // Copiando o nome
        memset(temp, 0, TAM);
        int pos_old = ++pos;
        pos = searchChar(';', pos, str);
        strncpy(temp, str + pos_old, pos - pos_old);
        strcpy(atual.Name, temp);

        // Copiando o tipo
        memset(temp, 0, TAM);
        pos_old = ++pos;
        pos = searchChar(';', pos, str);
        strncpy(temp, str + pos_old, pos - pos_old);
        strcpy(atual.Type, temp);

        // Copiando a galaxia
        memset(temp, 0, TAM);
        strcpy(temp, str + pos + 1);
        strcpy(atual.Galaxy, temp);

        Append(lst, atual);
    }

    fclose(fptr);
}

int comparePlanets(const Planet p1, const Planet p2)
{
    return strcmp(p1.Name, p2.Name);
}

void splitPlanets(const Planet &planet, char *result, int resultSize)
{
    snprintf(result, resultSize, "%d;%s;%s;%s", planet.Code, planet.Name, planet.Type, planet.Galaxy);
}

void writePlanets(list<Planet> &lst)
{
    ofstream arquivo;

    node<Planet> *aux = lst.begin;
    arquivo.open(LOCAL);
    char temp[TAM * 2];
    for (int i = 0; i < lst.count; i++)
    {
        memset(temp, 0, TAM * 2);
        splitPlanets(aux->data, temp, sizeof(temp));
        arquivo << temp;
        aux = aux->next;
    }

    arquivo.close();
}

void _readInterger(int *value)
{
    while (!(cin >> *value))
    {
        cout << "Digite um valor inteiro válido!\n> ";
        cin.clear();
        cin.ignore(123, '\n');
    }
}

void readNewPlanet(Planet *planet)
{
    char temp[TAM];
    cout << "Digite o código do planetas\n> ";
    _readInterger(&planet->Code);
    cout << "Nome do planeta\n> ";
    cin >> temp;
    strcpy(planet->Name, temp);
    cout << "Tipo do planeta\n> ";
    cin >> temp;
    strcpy(planet->Type, temp);
    cout << "Galaxia pertencente\n> ";
    cin.ignore();
    fgets(temp, TAM, stdin);
    strcpy(planet->Galaxy, temp);
}
