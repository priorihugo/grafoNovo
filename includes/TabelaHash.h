#ifndef TABELAHASH_H
#define TABELAHASH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include "Vertice.h"

#pragma once

using namespace std;

class TabelaHash
{
public:
    TabelaHash(int tamanho);
    ~TabelaHash();

    TabelaHash* insere(int chave, Vertice* item);
    TabelaHash* remove(int chave);
    int getTamanhoTable();

    void imprimeComoTabela();

    Vertice *busca(int chave);
    No<Vertice> *buscaNO(int chave);
    No<Vertice>* setIterator(No<Vertice>* v);
    No<Vertice>* iteratorInicio();
    No<Vertice>* proximo();

    No<Vertice> *iterator;

private:

    vector<Lista<Vertice>*>* tabela;
    int index_iterator;
    int num_registros;
    int TAMANHO_LISTA;
    int hashFunction(int chave);
};

#endif
