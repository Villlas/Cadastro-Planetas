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

// Função para orientar outras funções no app.h
void printPlanet(const Planet planet)
{
    cout << "   ____________________________________________" << endl;
    cout << "   |                                          |" << endl;
    cout << "     Codigo: " << planet.Code << endl;
    cout << "     Nome: " << planet.Name << endl;
    cout << "     Tipo: " << planet.Type << endl;
    cout << "     Galaxia pertencente: " << planet.Galaxy;
    cout << "   |__________________________________________|" << endl;
}
// Função para orientar outras funções no app.h
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
        cout << "Não foi possível abrir o arquivo" << endl;
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

int compareByName(Planet p1, Planet p2)
{
    return strcasecmp(p1.Name, p2.Name);
}

int compareByCode(Planet p1, Planet p2)
{
    return p1.Code - p2.Code;
}

void splitPlanets(Planet &planet, char *result, int resultSize)
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
    cout << "> ";
    while (!(cin >> *value))
    {
        cout << "Digite um valor inteiro válido!\n> ";
        cin.clear();
        cin.ignore(123, '\n');
    }
}

// Para o arquivo main.cpp
void readNewPlanet(Planet *newPlanet)
{
    char temp[TAM];
    cout << "Digite o código do planetas\n> ";
    _readInterger(&newPlanet->Code);
    cout << "Nome do planeta (utilize \"-\" no lugar de espaço)\n> ";
    cin.ignore();
    fgets(temp, TAM, stdin);
    temp[strcspn(temp, "\n")] = 0;
    strcpy(newPlanet->Name, temp);
    cout << "Tipo do planeta\n> ";
    cin >> temp;
    strcpy(newPlanet->Type, temp);
    cout << "Galaxia pertencente\n> ";
    cin.ignore();
    fgets(temp, TAM, stdin);
    strcpy(newPlanet->Galaxy, temp);
}

void showOnePlanet(list<Planet> &lst)
{
    int temp;
    quickSort(lst.begin, lst.end, compareByCode);
    PrintList(lst, PrintRemove, true);
    cout << "Deseja ver dados de qual planeta?\n> ";
    _readInterger(&temp);
    node<Planet> *aux = get(lst, temp);
    printPlanet((aux->data));
    cin.ignore();
}

void changePlanet(list<Planet> &lst)
{
    int temp;
    quickSort(lst.begin, lst.end, compareByCode);
    PrintList(lst, PrintRemove, true);
    cout << "Deseja alterar dados de qual planeta?\n> ";
    _readInterger(&temp);
    node<Planet> *aux = get(lst, temp);
    cout << "O que você deseja alterar?" << endl;
    cout << "[1] Codigo" << endl;
    cout << "[2] Nome" << endl;
    cout << "[3] Tipo" << endl;
    cout << "[4] Galaxia" << endl;
    _readInterger(&temp);
    switch (temp)
    {
    case 1:
        cout << "Digite o novo Código do planeta" << endl;
        _readInterger(&aux->data.Code);
        break;
    case 2:
        cout << "Digite o novo nome do planeta (utilize \"-\" no lugar de espaço)" << endl;
        cin.ignore();
        fgets(aux->data.Name, TAM, stdin);
        aux->data.Name[strcspn(aux->data.Name, "\n")] = 0;
        break;
    case 3:
        cout << "Digite o novo nome do tipo\n> ";
        cin >> aux->data.Type;
        break;
    case 4:
        cout << "Digite o novo nome da galáxia\n";
         cin.ignore();
        fgets(aux->data.Galaxy, TAM, stdin);
        aux->data.Name[strcspn(aux->data.Galaxy, "\n")] = 0;
        break;
    default:
        cout << "Escolha inválida" << endl;
        break;
    }
}

void removePlanet(list<Planet> &lst)
{
    int temp;
    quickSort(lst.begin, lst.end, compareByCode);
    PrintList(lst, PrintRemove, true);
    _readInterger(&temp);
    Remove(lst, temp);
    cin.ignore();
}

void showAllPlanets(list<Planet> &lst, char *SO)
{
    int choose;
    cout << "Deseja organizar\n[1]ordem Alfabetica (BubbleSort)\n[2]Por Codigo(quickSort)\n> ";
    _readInterger(&choose);
    if (choose == 1)
        BubbleSort(lst, compareByName);
    else
        quickSort(lst.begin, lst.end, compareByCode);
    system(SO);
    PrintList(lst, printPlanet);
    cin.ignore();
}

void searchPlanetByBinary(list<Planet> &lst, char *SO)
{
    // Busca Binária com dois elementos diferentes
    system(SO);
    int choice;
    cout << "Deseja procurar por:" << endl;
    cout << "[1] Nome" << endl;
    cout << "[2] Codigo\n> ";
    _readInterger(&choice);
    Planet searchPlanet;
    node<Planet> *result;
    switch (choice)
    {
    case 1:
        quickSort(lst.begin, lst.end, compareByName);
        char searchName[TAM];
        cout << "Digite o nome do planeta que deseja procurar no banco\n> ";
        cin >> searchName;
        strcpy(searchPlanet.Name, searchName);
        result = binarySearch(lst, searchPlanet, compareByName);
        if (result != nullptr)
        {
            cout << "Planeta Encontrado!" << endl;
            printPlanet(result->data);
            return;
        }
        cout << "Planeta nao encontrado" << endl;
        break;
    case 2:
        quickSort(lst.begin, lst.end, compareByCode);
        int searchCode;
        cout << "Digite o codigo do planeta: ";
        cin >> searchCode;

        searchPlanet.Code = searchCode;
        result = binarySearch(lst, searchPlanet, compareByCode);
        if (result != nullptr)
        {
            cout << "Planeta Encontrado!" << endl;
            printPlanet(result->data);
            return;
        }
        cout << "Planeta nao encontrado" << endl;
        break;
    default:
        cout << "Escolha Invalida!" << endl;
    }
}

void searchPlanetBySequencial(list<Planet> &lst, char *SO)
{
    system(SO);
    int choice;
    cout << "Deseja procurar por:" << endl;
    cout << "[1] Nome" << endl;
    cout << "[2] Codigo\n> ";
    _readInterger(&choice);
    Planet searchPlanet;
    node<Planet> *result;
    switch (choice)
    {
    case 1:
        quickSort(lst.begin, lst.end, compareByCode); // Para embaralhar a lista
        char searchName[TAM];
        cout << "Digite o nome do planetas\n> ";
        cin >> searchName;
        strcpy(searchPlanet.Name, searchName);
        result = sequentialSearch(lst, searchPlanet, compareByName);
        if (result != nullptr)
        {
            cout << "Planeta Encontrado!" << endl;
            printPlanet(result->data);
            return;
        }
        cout << "Planeta nao encontrado" << endl;
        break;

    case 2:
        quickSort(lst.begin, lst.end, compareByName); // Para embaralhar a lista
        int searchCode;
        cout << "Digite o codigo do planeta";
        _readInterger(&searchCode);
        searchPlanet.Code = searchCode;
        result = sequentialSearch(lst, searchPlanet, compareByCode);
        if (result != nullptr)
        {
            cout << "Planeta Encontrado!" << endl;
            printPlanet(result->data);
            return;
        }
        cout << "Planeta nao encontrado" << endl;
        break;

    default:
        break;
    }
}

void searchPlanet(list<Planet> &lst, char *SO)
{
    system(SO);
    int choice;
    cout << "Deseja procurar por:" << endl;
    cout << "[1] Pesquisa Binaria" << endl;
    cout << "[2] Pesquisa Sequencial\n> ";
    _readInterger(&choice);
    if (choice == 1)
        searchPlanetByBinary(lst, SO);
    else if (choice == 2)
        searchPlanetBySequencial(lst, SO);
    else
        cout << "Escolha inválida!" << endl;
}