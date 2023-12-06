#include "../includes/Vertice.h"

Vertice::Vertice(int novoId, float novoPeso , int coordX , int coordY)
{
    this->id = novoId;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->peso = novoPeso;
    this->visitado = false;
    this->coordX = coordX;
    this->coordY = coordY;

    this->cor = -1;

    this->arestas = new Lista<Aresta>();
}

Vertice::Vertice(Vertice* copia)
{
    id = copia->id;
    grauEntrada = copia->grauEntrada;
    grauSaida = copia->grauEntrada;
    peso = copia->peso;
    visitado = copia->visitado;
    arestas = new Lista<Aresta>();

    copia->getArestas()->iterator = copia->getArestas()->iteratorInicio();

    while(copia->getArestas()->iterator != nullptr)
    {

        arestas->insereInicio(copia->getArestas()->iterator->getData());
        copia->getArestas()->proximo();
    }
}


Vertice::~Vertice()
{
    id = -1;
    grauEntrada = 0;
    grauSaida = 0;
    peso = 0;
    arestas->limpaLista();
    delete arestas;
}

Vertice *Vertice::insereAresta(Vertice *destino, float peso,bool ehRetorno)
{
    if (destino == nullptr)
        return nullptr;

    //destino->imprime();
    Aresta *novaAresta = new Aresta(peso, destino , destino->getId());
    novaAresta->setEhRetorno(ehRetorno);

    if (arestas->busca(novaAresta->getDestino()->getId()) == nullptr)
    {
        arestas->insereFinal(novaAresta);
    }
}
Vertice *Vertice::removeAresta(int destino_id)
{
    arestas->deleta(destino_id);
}
Vertice *Vertice::removeTodasArestas(bool ehDirecionado)
{
}
Aresta *Vertice::buscaAresta(int destino_id)
{
    return arestas->busca(destino_id);
}

void Vertice::imprime()
{

    cout << "Vertice " << this->id << endl;
    cout << "{ "<< endl;
    cout << "   grauEntrada " << this->grauEntrada << endl;
    cout << "   grauSaida " << this->grauSaida << endl;
    cout << "   peso " << this->peso << endl;
    cout << "   visitado " << std::boolalpha <<  this->visitado << endl;
    cout << "   arestas " << endl;
    this->arestas->imprimeLista();
    cout << " }"<< endl;

}

