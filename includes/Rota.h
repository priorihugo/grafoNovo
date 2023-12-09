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
        this->capacidade_restante = capacidade;
        this->capacidade_maxima = capacidade;
        this->porcentagemParaVolta = 0.5;
        this->distanciaThreshold = 0;
        this->custo = 0;
    };
    ~Rota()
    {

        delete tuplas;
    }
    // float getCusto()
    // {
    //     float custo = 0;
    //     tuplas->iterator = tuplas->iteratorInicio();
    //     while (tuplas->iterator != nullptr)
    //     {
    //         custo += tuplas->iterator->getData()->getPeso();
    //         tuplas->proximo();
    //     }
    //     return custo;
    // }

    float getCusto()
    {
        return this->custo;
    }

    float getCapacidadeRestante()
    {
        return capacidade_restante;
    }

    float getCapacidadeMaxima()
    {
        return capacidade_maxima;
    }

    float getPorcentagemParaVolta()
    {
        return porcentagemParaVolta;
    }

    float getThreshold()
    {
        return distanciaThreshold;
    }

    void insere(Tupla *t)
    {
        capacidade_restante -= t->getPeso();
        custo += t->getPeso();

        if (capacidade_restante > (capacidade_maxima * this->porcentagemParaVolta) && distanciaThreshold == 0)
        {       
            distanciaThreshold = custo;
        }

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
    float capacidade_restante;
    float capacidade_maxima;
    float porcentagemParaVolta;
    float distanciaThreshold;

    float custo;

    Lista<Tupla> *tuplas;
};

#endif // ROTA_H
