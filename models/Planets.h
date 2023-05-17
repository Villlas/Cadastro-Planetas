#include <iostream>

#define TAM 100

using namespace std;

struct Planet
{
    u_int32_t Id;
    char Name[TAM];
    char Type[TAM];
    char Galaxy[TAM];
};

void printPlanet(Planet planet)
{
    cout << "-------------------------------" << endl;
    cout << "ID: " << planet.Id << endl;
    cout << "Nome: " << planet.Name << endl;
    cout << "Tipo: " << planet.Type << endl;
    cout << "Galaxia pertencente: " << planet.Galaxy;
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

void swapPlanet(Planet *p1, Planet *p2)
{
    Planet temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

template <typename T>
void QuickSort(list<T> &lst, int began, int end)
{
    int i, j;
    i = began;
    j = end - 1;
    Planet pivot;
    node<T> *temp = get(lst, (began + end) / 2);
    pivot = temp->data;
    while (i <= j)
    {
        node<T> *aux1 = get(lst, i);
        while (aux1->data.Id < pivot.Id && i < end && aux1 != nullptr)
        {
            i++;
            aux1 = aux1->next;
        }
        node<T> *aux2 = get(lst, j);
        while (aux2->data.Id > pivot.Id && j > began && aux2 != nullptr)
        {
            j--;
            aux2 = aux2->next;
        }
        if (i <= j)
        {
            swapPlanet(&(aux1->data), &(aux2->data));
            i++;
            j--;
        }
    }
    if (j > began)
        QuickSort(lst, began, j + 1);
    if (i < end)
        QuickSort(lst, i, end);

}