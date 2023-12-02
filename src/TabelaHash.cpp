#include "../includes/TabelaHash.h"

using namespace std;

int TabelaHash::hashFunction(int chave)
{
    //cout <<"hash function" << endl;
    return chave % TAMANHO_LISTA;
};

TabelaHash::TabelaHash(int tamanho)
{

    index_iterator = 0;
    num_registros = 0;

    this->TAMANHO_LISTA = tamanho;
    tabela = new vector<Lista<Vertice>*>;
    tabela->resize(tamanho);

    for (size_t i = 0; i < tabela->size(); i++)
    {
        tabela->at(i) = new Lista<Vertice>();
    }
}

TabelaHash::~TabelaHash()
{
    for (size_t i = 0; i < tabela->size(); i++)
    {
        tabela->at(i)->limpaLista();
        delete tabela->at(i);
    }
}

Vertice *TabelaHash::busca(int chave)
{
    int indice = this->hashFunction(chave);
    Lista<Vertice> *lista = tabela->at(indice);
    return lista->busca(chave);
}

int TabelaHash::getTamanhoTable()
{
    return this->TAMANHO_LISTA;
}

TabelaHash *TabelaHash::insere(int chave, Vertice *item)
{
    int indice = this->hashFunction(chave);
    Lista<Vertice> *lista = tabela->at(indice);
    lista->insereFinal(item);
    num_registros++;
    return this;
};

TabelaHash *TabelaHash::remove(int chave)
{
    int indice = this->hashFunction(chave);
    Lista<Vertice> *lista = tabela->at(indice);
    lista->deleta(chave);
    num_registros--;
    return this;
};
No<Vertice> *TabelaHash::iteratorInicio()
{
    // cada indice da hash
    index_iterator = 0;
    this->iterator = nullptr;
    for (size_t index = 0; index < TAMANHO_LISTA; index++)
    {
        Lista<Vertice> *listaVertices = tabela->at(index);
        if(listaVertices != nullptr && listaVertices->iteratorInicio()!= nullptr)
        {
            index_iterator = index;
            this->iterator = listaVertices->iteratorInicio();
            return this->iterator;
        }
    }
    return nullptr;
}


No<Vertice>* TabelaHash::setIterator(No<Vertice>* v)
{
    // cada indice da hash
    //this->imprimeComoTabela();

    index_iterator = 0;
    this->iterator = nullptr;
    for (size_t index = 0; index < TAMANHO_LISTA; index++)
    {
        Lista<Vertice> *listaVertices = tabela->at(index);
        if(listaVertices != nullptr && listaVertices->busca(v->getData()->getId()) != nullptr)
        {
            index_iterator = index;
            this->iterator = listaVertices->buscaNo(v->getData()->getId());
            return this->iterator;
        }
    }
    return nullptr;
}

No<Vertice> *TabelaHash::proximo()
{

    if (iterator == nullptr)
        return nullptr;


    //cout <<"iterator id antes " << iterator->getData()->getId() << endl;
    //cout << "index_iterator " << index_iterator << endl;

    if (iterator->getProximo() == nullptr)
    {
        //cout << "fim da lista " << endl;

        while (index_iterator < TAMANHO_LISTA -1 )
        {
            index_iterator++;
            Lista<Vertice>* lista = this->tabela->at(index_iterator);

            if(lista->iteratorInicio()!=nullptr)
            {
                this->iterator = lista->iteratorInicio();
                return this->iterator;
            }
        }
        iterator = iterator->getProximo();
        return iterator;
    }
    else
    {
        iterator = iterator->getProximo();
        return iterator;
    }
}

void TabelaHash::imprimeComoTabela()
{
    for (size_t index = 0; index < TAMANHO_LISTA; index++)
    {
        Lista<Vertice> *listaVertices = tabela->at(index);
        cout << "[" << index << "]" ;
        listaVertices->imprimeLista();
    }
}
