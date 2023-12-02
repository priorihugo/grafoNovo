#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <limits>

#include "No.h"
#include "Aresta.h"
#include "Vertice.h"
#include "Tupla.h"


#pragma once

template <typename T>
class Lista{
public:
    Lista();
    ~Lista();

    Lista* insereInicio(T *item , int index = 0);
    Lista* insereFinal(T *item , int index = 0);
    Lista *deleta(int id, bool deleteData = false);
    T *busca(int id);
    T* desempilhaPrimeiro();
    T* visitaPrimeiro();
    T* encontraMaiorPeso();

    void imprimeLista();

    bool ehVazia();
    void limpaLista();

    No<T> *iteratorInicio();
    No<T> *iteratorFim();
    No<T> *proximo();
    No<T> *anterior();
    No<T> *buscaNo(int id);

    No<T> *iterator;

private:
    void deleteAuxiliar(No<T> *item , bool deleteData = false);

    No<T> *inicio;
    No<T> *fim;
    int tamanho = 0;
};

#endif // LISTA_H
