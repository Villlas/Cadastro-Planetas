#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

#define TAM 100
#define LOCAL "Data/dataBase.csv"

template <typename T>
struct node
{
    T data;
    node<T> *next = nullptr;
    node<T> *previous = nullptr;
};

template <typename T>
struct list
{
    node<T> *begin = nullptr;
    node<T> *end = nullptr;
    int count = 0;
};

template <typename T>
void Append(list<T> &lst, T newData)
{
    node<T> *newNode = new node<T>;
    newNode->data = newData;

    if (lst.count == 0)
        lst.begin = lst.end = newNode;
    else
    {
        newNode->previous = lst.end;
        lst.end->next = newNode;
        lst.end = newNode;
    }
    lst.count++;
}

template <typename T>
void CleanMemory(list<T> &lst)
{
    while (lst.count > 0)
    {
        node<T> *aux = lst.end;
        lst.end = lst.end->previous;
        delete aux;
        lst.count--;
    }
    lst.begin = lst.end = nullptr;
}

template <typename T>
void PrintList(list<T> &lst, void (*funcPrint)(T))
{
    node<T> *aux = lst.begin;
    while (aux != nullptr)
    {
        funcPrint(aux->data);
        aux = aux->next;
    }
    cout << "\n-------------------------------" << endl;
}

template <typename T>
node<T> *get(list<T> lst, u_int32_t position)
{
    try
    {
        if (position > lst.count - 1)
            throw "Posição inválida";
    }
    catch (string e)
    {
        cout << e << endl;
    }

    int now = 0;
    node<T> *aux = lst.begin;
    while (now < position)
    {
        now++;
        aux = aux->next;
    }

    return aux;
}

template <typename T>
void remove(list<T> &lst, u_int32_t position)
{
    try
    {
        if (position >= lst.count)
            throw "Posição inválida!";
    }
    catch (string e)
    {
        cout << e << endl;
        return;
    }

    node<T> *aux = get(lst, position);
    if (aux->next != nullptr)
        aux->next->previous = aux->previous;
    else
        lst.end = aux->previous;

    if (aux->previous != nullptr)
        aux->previous->next = aux->next;
    else
        lst.begin = aux->next;
    delete aux;
    lst.count--;
}



