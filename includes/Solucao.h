#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <vector>
#include <string>
#include <sstream>
#include "Rota.h"

using namespace std;


class Solucao
{
    public:
        Solucao();
        Solucao(int tamanho , int capacidade);

        virtual ~Solucao();

        void imprime();

        float getQualidade();

        Rota* getRota(int index);
        string getParaTXT();

    private:
        vector<Rota*>* rotas;
};

#endif // SOLUCAO_H
