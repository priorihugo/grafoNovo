#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>

#include "Tupla.h"
#include "TabelaHash.h"

#pragma once

using namespace std;

class Grafo
{
	private:
		int ordem = 0;
		bool eh_direcionado;
		bool tem_peso_aresta;
		bool tem_peso_vertice;
		///lista de vertices
        TabelaHash *vertices;

public:

    Grafo(int ehOrdenado, int temDirecao, int temPesoAresta, int temPesoVertice);
    ~Grafo();

    ///getters imediatos
    int getOrdem()
    {
        return this->ordem;
    };
    bool direcionado()
    {
        return eh_direcionado;
    };
    bool temPesoAresta()
    {
        return tem_peso_aresta;
    };
    bool temPesoVertice()
    {
        return tem_peso_vertice;
    };

    ///manipulacao da lista de vertices
    bool insereVertice(int id_origem,float peso , int coordX = 0 , int coordY = 0);
    void removeVertice(int id_origem);
    bool insereAresta(int id_origem, int id_destino, float peso = 1,  bool ehRetorno = false);
    void removeAresta(int id_origem, int id_destino);

    void limpaMarcacao();


    Vertice* getVertice(int id);
    void geraDistanciasDeVertices();
    Grafo* buscaEmLargura(int id);

    bool aux(Grafo* resultado, TabelaHash* visitados, Vertice*  atual);
    Grafo* SGVI_fechoTransitivoIndireto(int id_origem, ofstream& output);
    float dijkstra(int id_origem ,int id_destino , ofstream& output );

    /*
    float floyd(int origem , int destino , ofstream& output);
    Grafo* SGVI_feixoTransitivoDireto(int id_origem , ofstream& output);
    Grafo* buscaEmProfundidade(int id , ofstream& output);
    void ordenacaoTopologica(ofstream& output);
    Grafo* agmPrim(ofstream& output);
    Grafo* agmKruskal(ofstream& output);
    */

    Grafo* algoritimoGulosoRoteamento(int numVeiculos , int id_origem);

    void imprimirGraphviz(string nome);

};

#endif
