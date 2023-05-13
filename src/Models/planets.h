#include <iostream>
#define TAM 100

using namespace std;

struct Planet
{
    int Id;
    char Name[TAM];
    char Type[TAM];
    char Galaxy[TAM];
};

void printPlanet(Planet planet) {
    cout << "-------------------------------" << endl;
    cout << "ID: "<< planet.Id << endl;
    cout << "Nome: "<< planet.Name << endl;
    cout << "Tipo: "<< planet.Type << endl;
    cout << "Galaxia pertencente: "<< planet.Galaxy;
}

int searchChar(char letter, int posi, char *line)
{
    int atual = posi;
    while (line[atual] != letter)
        atual++;
    return atual;
}


template <typename T>
void readPlanets(list<T> &lst)
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
        atual.Id = atoi(temp);

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
