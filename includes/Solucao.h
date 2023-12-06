#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <vector>
#include "Rota.h"

using namespace std;


class Solucao
{
    public:
        Solucao();
        Solucao(int tamanho);

        virtual ~Solucao();

        void imprime();

        float getQualidade();

        Rota* getRota(int index);

    private:
        vector<Rota*>* rotas;
};

#endif // SOLUCAO_H
