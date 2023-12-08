#ifndef ROTA_H
#define ROTA_H

#include "Tupla.h"
#include "Lista.h"
#include <vector>
#include <sstream>
#include <string>

#pragma once;

using namespace std;

class Rota
{
public:
    Rota(float capacidade = 100)
    {
        this->tuplas = new Lista<Tupla>();
        this->capacidade = capacidade;
    };
    ~Rota()
    {

        delete tuplas;
    }
    float getCusto()
    {
        float custo = 0;
        tuplas->iterator = tuplas->iteratorInicio();
        while (tuplas->iterator != nullptr)
        {
            custo += tuplas->iterator->getData()->getPeso();
            tuplas->proximo();
        }
        return custo;
    }

    void insere(Tupla *t)
    {
        capacidade -= t->getPeso();
        this->tuplas->insereInicio(t, 0);
        vertices++;
    }

    Tupla *getPonta()
    {
        this->tuplas->visitaPrimeiro();
    }

    void imprime()
    {
        this->tuplas->iterator = this->tuplas->iteratorInicio();
        while (this->tuplas->iterator != nullptr)
        {
            Tupla *t = this->tuplas->iterator->getData();
            cout << " - " << t->getId() << "P(" << t->peso << ")"
                 << "CR(" << t->capacidade_restante << ")";
            this->tuplas->proximo();
        }
        cout << " - " << endl;
    }

    string getParaTXT()
    {

        stringstream ss;
        this->tuplas->iterator = this->tuplas->iteratorInicio();
        while (this->tuplas->iterator != nullptr)
        {
            Tupla *t = this->tuplas->iterator->getData();
            ss << " - " << t->getId() << "P(" << t->peso << ")"
                 << "CR(" << t->capacidade_restante << ")";
            this->tuplas->proximo();
        }
        ss << " - " << endl;

        return ss.str();
    }

    int vertices = 0;

private:
    float capacidade;

    Lista<Tupla> *tuplas;
};

#endif // ROTA_H
