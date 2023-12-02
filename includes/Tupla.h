#ifndef TUPLA_H
#define TUPLA_H


#include "Vertice.h"

#pragma once

class Tupla
{
public:
    Vertice*destino;
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

private:
};

#endif // TUPLA_H
