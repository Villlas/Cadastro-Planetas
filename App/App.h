#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <utility>


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

    node<T> *aux = lst.begin;
    for (int i = 0; i < position; i++)
        aux = aux->next;

    return aux;
}

template <typename T>
void Remove(list<T> &lst, u_int32_t position)
{

    if (position >= lst.count)
    {
        cout << "Posição inválida" << endl;
        return;
    }

    if (lst.count == 0)
    {
        cout << "A lista está vazia" << endl;
        return;
    }

    node<T> *aux = get(lst, position);
    (aux->next != nullptr) ? aux->next->previous = aux->previous : lst.end = aux->previous;
    (aux->previous != nullptr) ? aux->previous->next = aux->next : lst.begin = aux->next;
    delete aux;
    lst.count--;
}

template <typename T>
void swapNode(list<T> &lst, u_int32_t positionA, u_int32_t positionB)
{
    node<T> *nodeA = get(lst, positionA);
    node<T> *nodeB = get(lst, positionB);
    T aux = nodeA->data;
    nodeA->data = nodeA->data;
    nodeB->data = aux;
}
/* template <typename T>
node<T> *partition(list<T> &lst)
{
    Planet pivot = lst.end->data;
    node *aux = lst.begin;

    for (node *temp = lst.begin)
} */




template <typename T>
void insertIdVector(list<T> &lst, int *vector)
{
    int i = 0;
    node<T> *aux = lst.begin;
    while (aux != nullptr)
    {
        vector[i] = aux->data.Id;
        i++;
        aux = aux->next;
    }
}
template <typename T>
void BubbleSort(list<T> &lst, int (*funcComp)(T, T))
{
    bool isOrder = false;
    while (!isOrder)
    {
        isOrder = true;
        for (int i = 1; i < lst.count; i++)
        {
            node<T> *nodeA = get(lst, i - 1);
            node<T> *nodeB = get(lst, i);
            if (funcComp(nodeA->data, nodeB->data) > 0)
            {
                isOrder = false;
                swap(lst, i, i - 1);
            }
        }
    }
}
