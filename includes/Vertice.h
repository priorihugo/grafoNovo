#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
#include <fstream>
#include <string>

#include "Lista.h"


#include "Aresta.h"




#pragma once

using namespace std;

template <typename T>
class Lista;

class Aresta;
class Vertice
{
private:

	int id;
	int coordX = 0 , coordY = 0;
	int grauEntrada;
	int grauSaida;
	float peso;
	bool visitado;

	Lista<Aresta> *arestas;

public:
	Vertice(int novoId, float novoPeso , int coordX = 0 , int coordY = 0);
	Vertice(Vertice* copia);
	~Vertice();

	int getId() { return this->id; };
	int getGrauSaida() { return this->grauSaida; };
	int getGrauEntrada() { return this->grauEntrada; };
	float getPeso() { return this->peso; };
	bool ehVisitado() { return visitado; };
	int getX(){ return this->coordX; };
	int getY(){	return this->coordY; };

	void setVisitado(bool valor) { this->visitado = valor; };
	void incSaida() { grauSaida++; };
	void incEntrada() { grauEntrada++; };
	void decSaida() { grauSaida--; };
	void decEntrada() { grauEntrada--; };
	void setPeso(float p) { this->peso = p; };

	Vertice *insereAresta(Vertice *destino, float peso , bool ehRetorno = false);
	Vertice *removeAresta(int destino_id);
	//Vertice *removeAresta(Vertice *destino);
	Vertice *removeTodasArestas(bool ehOrdenado);
	Aresta *buscaAresta(int destino_id);
	//Aresta *buscaAresta(Vertice *destino);

	Lista<Aresta>* getArestas(){ return this->arestas;};

	void imprime();

	bool compara(Vertice *item)
	{
		return this == item;
	};
	bool comparaId(int id)
	{
		return this->getId() == id;
	};
};

#endif
