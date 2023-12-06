#ifndef TUPLA_H
#define TUPLA_H

#include "Vertice.h"
#include <iostream>

using namespace std;

#pragma once

class Tupla
{
public:

    Vertice* destino;
    int verticeId;
    int index_rota;
    int capacidade_restante;
    float peso;

    bool comparaId(int id){
        return this->verticeId == id;
    }

    int getId(){
        return this->verticeId;
    }

    float getPeso(){
        return peso;
    }

    void imprime(){

        cout << "vertice id " << verticeId << endl;
        cout << "index_rota " << index_rota << endl;
        cout << "capacidade_restante " << capacidade_restante <<endl;
        cout << "peso " << peso <<endl;


    }

private:
};

#endif // TUPLA_H
