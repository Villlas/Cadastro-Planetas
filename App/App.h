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
node<T> *partition(node<T> *start, node<T> *end)
{
    /*
    Função partition é um complemento para a função quickSort, a qual tem a função
    de escolher um elemento como um pivô, que no meu caso eu fiz escolhendo o último,
    e durante a execução a função vai particionando a lista para que as entidades menores
    que o pivô escolhido fique a esquerda e os maiores fiquem a direita do mesmo.
    Esse homem indiano me salvou
    https://www.youtube.com/watch?v=ms_rjPaUNqs&t=870s
    */
    int pivot = end->data.Code;
    node<T> *aux1 = start->previous;

    for (node<T> *aux2 = start; aux2 != end; aux2 = aux2->next)
    {
        if (aux2->data.Code <= pivot)
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
void quickSort(node<T> *start, node<T> *end)
{
    if (end != nullptr && start != end && start != end->next)
    {
        node<T> *pivot = partition(start, end);

        quickSort(start, pivot->previous);
        quickSort(pivot->next, end);
    }
}

// Funções Responsáveis Pela busca binária
// OBS Se for pesquisar por nome use o bubble sort para organizar
template <typename T>
node<T> *binarySearchRecursive(node<T> *start, node<T> *end, T &searchData, bool byName)
{
    if (start == nullptr || end == nullptr || start == end->next)
        return nullptr;

    node<T> *mid = start;
    int cmp;

    if (byName)
    {
        cmp = strcasecmp(mid->data.Name, searchData.Name);
    }
    else
        cmp = (mid->data.Code == searchData.Code) ? 0 : (mid->data.Code < searchData.Code) ? -1
                                                                                           : 1;

    if (cmp == 0)
        return mid;
    else if (cmp < 0)
        return binarySearchRecursive(mid->next, end, searchData, byName);
    else
        return binarySearchRecursive(start, mid->previous, searchData, byName);
}

template <typename T>
node<T> *binarySearch(list<T> &lst, T &searchData, bool byName)
{
    node<T> *start = lst.begin;
    node<T> *end = lst.end;

    return binarySearchRecursive(start, end, searchData, byName);
}

template <typename T>
node<T> sequentialSearch(list<T> &lst, T &searchData, int (*funcComp)(T &, T &))
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

