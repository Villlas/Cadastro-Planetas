#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

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
    cout << "Memoria limpa com sucesso" << endl;
}

template <typename T>
void PrintList(list<T> &lst, void (*funcPrint)(T), bool showID = false)
{
    node<T> *aux = lst.begin;
    int id = 0;
    while (aux != nullptr)
    {
        if (showID)
            printf("[%d] ", id);
        funcPrint(aux->data);
        aux = aux->next;

        id++;
    }
    cout << endl;
}

template <typename T>
node<T> *get(list<T> lst, unsigned int position)
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
void Remove(list<T> &lst, unsigned int position)
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

// Funções para implementar o bubble sort
template <typename T>
void swap(list<T> &lst, int positionA, int positionB)
{
    node<T> *node1 = get(lst, positionA);
    node<T> *node2 = get(lst, positionB);
    T aux = node1->data;
    node1->data = node2->data;
    node2->data = aux;
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

// Funções responsáveis pelo quick sort
template <typename T>
void swapNode(node<T> *nodeA, node<T> *nodeB)
{
    T aux = nodeA->data;
    nodeA->data = nodeB->data;
    nodeB->data = aux;
}

template <typename T>
node<T> *partition(node<T> *start, node<T> *end, int(*funcComp)(T, T))
{

    T pivot = end->data;
    node<T> *aux1 = start->previous;

    for (node<T> *aux2 = start; aux2 != end; aux2 = aux2->next)
    {
        if (funcComp(aux2->data, pivot) <= 0)
        {
            aux1 = (aux1 == nullptr) ? start : aux1->next;
            swapNode(aux1, aux2);
        }
    }
    aux1 = (aux1 == nullptr) ? start : aux1->next;
    swapNode(aux1, end);

    return aux1;
}

template <typename T>
void quickSort(node<T> *start, node<T> *end, int(*funcComp)(T, T))
{
    if (end != nullptr && start != end && start != end->next)
    {
        node<T> *pivot = partition(start, end, funcComp);

        quickSort(start, pivot->previous, funcComp);
        quickSort(pivot->next, end, funcComp);
    }
}


template <typename T>
node<T> *binarySearchRecursive(node<T> *start, node<T> *end, T &searchData, int (*funcComp)(T, T))
{
    if (start == nullptr || end == nullptr || start == end->next)
        return nullptr;

    node<T> *mid = start;
    int compResult = funcComp(mid->data, searchData);

    if (compResult == 0)
        return mid;
    else if (compResult < 0)
        return binarySearchRecursive(mid->next, end, searchData, funcComp);
    else
        return binarySearchRecursive(start, mid->previous, searchData, funcComp);
}

template <typename T>
node<T> *binarySearch(list<T> &lst, T &searchData, int (*funcComp)(T, T))
{
    node<T> *start = lst.begin;
    node<T> *end = lst.end;

    return binarySearchRecursive(start, end, searchData, funcComp);
}

template <typename T>
node<T> *sequentialSearch(list<T> &lst, T &searchData, int (*funcComp)(T, T))
{
    node<T> *aux = lst.begin;

    while (aux != nullptr)
    {
        if (funcComp(aux->data, searchData) == 0)
            return aux; // Se encontrar!
        aux = aux->next;
    }

    // Caso não encontre nada!
    return nullptr;
}
