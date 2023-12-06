#include "../includes/Lista.h"

using namespace std;

template <typename T>
Lista<T>::Lista()
{
    tamanho = 0;
    fim = nullptr;
    inicio = nullptr;
    iterator = nullptr;
}

template <typename T>
Lista<T>::~Lista()
{
    tamanho = 0;
    fim = nullptr;
    inicio = nullptr;

    this->limpaLista();
}

template <typename T>
Lista<T> *Lista<T>::insereInicio(T *item, int index)
{
    if(item == nullptr) return this;
     No<T>* novoItem = new No<T>(item, index);

    // se lista vazia
    if (this->inicio == nullptr && this->fim == nullptr)
    {
        inicio = fim = novoItem;
        //novoItem->proximo = nullptr;
        novoItem->setProximo(nullptr);
        //novoItem->anterior = nullptr;
        novoItem->setAnterior(nullptr);
    }
    else
    {
        //novoItem->proximo = inicio;
        novoItem->setProximo(inicio);
        //novoItem->anterior = nullptr;
        novoItem->setAnterior(nullptr);
        //inicio->anterior = novoItem;
        inicio->setAnterior(novoItem);

        this->inicio = novoItem;
    }
    tamanho++;
}

template <typename T>
Lista<T> *Lista<T>::insereFinal(T *item, int index)
{
    if(item == nullptr) return this;
    No<T>* novoItem = new No<T>(item, index);


    // se lista vazia
    if (this->inicio == nullptr && this->fim == nullptr)
    {
        inicio = fim = novoItem;
        novoItem->setProximo(nullptr);
        novoItem->setAnterior(nullptr);
    }
    else
    {
        novoItem->setAnterior(fim);
        novoItem->setProximo(nullptr);
        fim->setProximo(novoItem);
        fim = novoItem;
    }

    tamanho++;
    return this;
}

template <typename T>
void Lista<T>::deleteAuxiliar(No<T> *iteracaoAtual, bool deleteData)
{
    if (iteracaoAtual == inicio)
    {
        inicio->setAnterior(nullptr);
        inicio = iteracaoAtual->getProximo();
    }

    if (iteracaoAtual == fim)
    {
        fim->setProximo(nullptr);
        fim = iteracaoAtual->getAnterior();
    }

    if (iteracaoAtual->getAnterior() != nullptr)
        iteracaoAtual->getAnterior()->setProximo(iteracaoAtual->getProximo());

    if (iteracaoAtual->getProximo() != nullptr)
        iteracaoAtual->getProximo()->setAnterior(iteracaoAtual->getAnterior());


    if(deleteData)
    {
        T* data = iteracaoAtual->getData();
        iteracaoAtual->setData(nullptr);
        delete data;
    }

    delete iteracaoAtual;
}


template <typename T>
Lista<T> *Lista<T>::deleta(int id, bool deleteData)
{
    No<T> *busca = this->buscaNo(id);

    if (busca != nullptr)
    {
        deleteAuxiliar(busca);
    }

    tamanho--;
    return this;
}

template <typename T>
T* Lista<T>::busca(int id)
{
    No<T> *iteracaoAtual = inicio;

    while (iteracaoAtual != nullptr)
    {
        if (iteracaoAtual->getData()->comparaId(id))
        {
            return iteracaoAtual->getData();
        }
        iteracaoAtual = iteracaoAtual->getProximo();
    }

    return nullptr;
}

template <typename T>
No<T>* Lista<T>::buscaNo(int id)
{
    No<T> *iteracaoAtual = inicio;

    while (iteracaoAtual != nullptr)
    {
        if (iteracaoAtual->getData()->comparaId(id))
        {
            return iteracaoAtual;
        }
        iteracaoAtual = iteracaoAtual->getProximo();
    }

    return nullptr;
}

template <typename T>
No<T> *Lista<T>::iteratorInicio()
{
    return this->inicio;
}

template <typename T>
No<T> *Lista<T>::iteratorFim()
{
    return this->fim;
}

template <typename T>
No<T>* Lista<T>::proximo()
{
    if (this->iterator != nullptr)
    {
        iterator = iterator->getProximo();
        return iterator;
    }
    return nullptr;
}

template <typename T>
No<T>* Lista<T>::anterior()
{
    if (this->iterator != nullptr)
    {
        iterator = iterator->getAnterior();
        return iterator;
    }
    return nullptr;
}

template <typename T>
bool Lista<T>::ehVazia()
{
    return inicio == fim && inicio == nullptr;
}

template <typename T>
void Lista<T>::limpaLista()
{

    No<T>* iteracao = inicio;

    while (iteracao != nullptr)
    {
        No<T>* toDelete = iteracao;
        iteracao = iteracao->getProximo();
        delete toDelete;
    }

    inicio = fim = nullptr;
}

template <typename T>
void Lista<T>::imprimeLista()
{

    No<T>* it = inicio;

    while(it != nullptr)
    {
        if(it->getAnterior() == nullptr)
        {
            cout << "<-- ";
        }

        cout << it->getData()->getId() << " ";

        if(it->getProximo() == nullptr)
        {
            cout << "--> ";
        }

        it = it->getProximo();
    }
    cout << endl;
}

template <typename T>
T* Lista<T>::desempilhaPrimeiro()
{
    if(this->ehVazia()) return nullptr;

    No<T>* retorno = inicio;

    deleta(inicio->getData()->getId());


    tamanho--;
    retorno->setProximo(nullptr);
    retorno->setAnterior(nullptr);

    return retorno->getData();
}

template <typename T>
T* Lista<T>::visitaPrimeiro()
{
    if(this->ehVazia()) return nullptr;

    No<T>* retorno = inicio;
    return retorno->getData();
}

template <typename T>
T* Lista<T>::encontraMaiorPeso()
{

    if (ehVazia())
    {
        return nullptr;
    }

    No<T> *temp = inicio;
    T *maiorPeso = nullptr;
    int maxPeso = std::numeric_limits<int>::min(); // Valor mínimo possível para int

    while (temp != nullptr)
    {
        T* data = temp->getData();
        if (data != nullptr)
        {
            if (data->getPeso() > maxPeso)
            {
                maxPeso = data->getPeso();
                maiorPeso = data;
            }
        }
        temp = temp->getProximo();
    }

    if (maiorPeso != nullptr)
    {
        return maiorPeso;
    }
    else
    {
        return nullptr;
    }
}


template class Lista<Vertice>;
template class Lista<Aresta>;
template class Lista<Tupla>;


