#define INT_MAX 2147483640/2
#define FLT_MAX 2147483640/2
#include "../includes/Grafo.h"

Grafo::Grafo(int ehOrdenado, int temDirecao, int temPesoAresta, int temPesoVertice)
{
    eh_direcionado = temDirecao == 1 ? true : false;
    tem_peso_aresta = temPesoAresta == 1 ? true : false;
    tem_peso_vertice = temPesoVertice == 1 ? true : false;

    this->vertices = new TabelaHash(2);
}
Grafo::~Grafo()
{
    delete vertices;
}

bool Grafo::insereVertice(int id_origem, float peso = 1, int coordX, int coordY)
{
    if (vertices->busca(id_origem) == nullptr)
    {
        vertices->insere(id_origem, new Vertice(id_origem, peso,coordX, coordY));
        ordem++;
        return true;
    }
    else
    {
        cout << "ID " << id_origem << " ja existe" << endl;
        return false;
    }
}
void Grafo::removeVertice(int id_origem)
{
    Vertice *v = vertices->busca(id_origem);
    // lembrar de decrementar o grau de entrada de todo vertice atingido e remover as arestas
    // que incidem sober o vertice a ser deletado
    if(v != nullptr)
    {
        Lista<Aresta>* lista = v->getArestas();
        lista->iterator = lista->iteratorInicio();

        //precisamos ir onde cada aresta incide e deletar conexões com este vertice
        while (lista->iterator != nullptr)
        {
            lista->iterator->getData()->getDestino()->decEntrada();
            lista->iterator->getData()->getDestino()->removeAresta(id_origem);

            lista->proximo();
        }
        vertices->remove(id_origem);
    }
}
bool Grafo::insereAresta(int id_origem, int id_destino, float peso, bool ehRetorno)
{
    //cout << "inserindo aresta origem: " << id_origem << " destino " << id_destino << endl;
    Vertice *origem = vertices->busca(id_origem);
    Vertice *destino = vertices->busca(id_destino);

    if(origem != nullptr && destino != nullptr)
    {
        peso = this->tem_peso_aresta ? peso : 1;
        origem->insereAresta(destino, peso, ehRetorno);
        origem->incSaida();

        if (!this->eh_direcionado)
        {
            destino->insereAresta(origem, peso, ehRetorno);
            destino->incEntrada();
        }
        return true;
    }
    return false;
}
void Grafo::removeAresta(int id_origem, int id_destino)
{
    Vertice *origem = vertices->busca(id_origem);
    Vertice *destino = vertices->busca(id_destino);

    if(origem != nullptr && destino != nullptr)
    {
        origem->removeAresta(destino->getId());
        origem->decSaida();

        if (!this->eh_direcionado)
        {
            destino->removeAresta(origem->getId());
            destino->decEntrada();
        }
    }
}

Vertice* Grafo::getVertice(int id)
{
    return this->vertices->busca(id);
}

void Grafo::geraDistanciasDeVertices()
{
    limpaMarcacao();

    float distancia = 0;
    //vertices->imprimeComoTabela();
    vertices->iterator = vertices->iteratorInicio();
    No<Vertice>*  atual = vertices->iterator;

    while(vertices->iterator != nullptr)
    {
        No<Vertice>* iteracao = vertices->iterator = vertices->iteratorInicio();
        while(iteracao != nullptr)
        {
            if(atual->getData()->getId() != iteracao->getData()->getId())
            {
                Vertice* dataI = iteracao->getData();
                Vertice* dataA = atual->getData();

                distancia = sqrt(pow(dataI->getX() - dataA->getX(), 2) + pow(dataI->getY() - dataA->getY(), 2));
                this->insereAresta(dataA->getId(), dataI->getId(), distancia, false);
            }
            iteracao = vertices->proximo();
        }
        vertices->setIterator(atual);
        atual = vertices->proximo();
    }
}

void Grafo::limpaMarcacao()
{


    vertices->iterator = vertices->iteratorInicio();
    while(vertices->iterator != nullptr)
    {
        Vertice* v = vertices->iterator->getData();
        v->setVisitado(false);
        vertices->proximo();
    }
}

void Grafo::imprimirGraphviz(string nome)
{
    ofstream output;
    string path = "./output/";
    path.append(nome);
    output.open(path + ".dot");

    cout << "Abrindo o arquivo " << endl;

    if (output.is_open())
    {
        string conector;
        if (this->direcionado())
        {
            /// inserindo no output um grafo direcionado
            output << "digraph " << nome <<" {" << endl;
            conector = " -> ";
            cout << "Grafo direcionado " << endl;
        }
        else
        {
            /// inserindo no output um grafo n�o direcionado
            output << "strict graph " << nome << " {" << endl;
            conector = " -- ";
            cout << "Grafo não direcionado " << endl;
        }

        Lista<Aresta> *lista;
        vertices->iterator = vertices->iteratorInicio();

        while (vertices->iterator != nullptr)
        {
            lista = vertices->iterator->getData()->getArestas();
            lista->iterator = lista->iteratorInicio();
            if(lista->iterator == nullptr)
            {
                output << vertices->iterator->getData()->getId() << endl;
            }
            else
            {
                while (lista->iterator != nullptr)
                {
                    Aresta *a = lista->iterator->getData();
                    output << vertices->iterator->getData()->getId() << conector << a->getDestino()->getId();

                    if(a->ehArestaRetorno()) output << " [ color=\"red\" ]";

                    output << endl;
                    lista->proximo();
                }
            }
            vertices->proximo();
        }
    }

    output << "}" << endl;
    output.close();


    string command = "dot -Tpng ";
    command = command.append(path);
    command = command.append(".dot -o ");
    command = command.append(path + ".png");

    cout << command << endl;
    system(command.data());
    system("pause");
}

Grafo* Grafo::SGVI_fechoTransitivoIndireto(int id_origem, ofstream& output)
{
    limpaMarcacao();

    int index = 0;

    Grafo* resultado = new Grafo(0,1,0,0);
    Vertice* verticeInicio = this->vertices->busca(id_origem);
    TabelaHash* visitados = new TabelaHash(2);

    if(verticeInicio == nullptr) return nullptr;

    resultado->insereVertice(verticeInicio->getId(), verticeInicio->getPeso());

    ///iterando todos os vertices do grafo atual
    this->vertices->iterator = this->vertices->iteratorInicio();
    while(this->vertices->iterator != nullptr)
    {
        aux(resultado, visitados,this->vertices->iterator->getData());
        //stringstream ss;
        //ss << index;
        //string str = ss.str();
        //std::string nome = "fecho_";
        //nome.append(str);
        //resultado->imprimirGraphviz(nome);
        this->vertices->proximo();
        index++;
    }

    resultado->imprimirGraphviz("fechoTransitivoIndireto");
    return resultado;
}

Grafo* Grafo::buscaEmLargura(int id)
{
    limpaMarcacao();

    Vertice* inicio = this->vertices->busca(id);
    Grafo* resultado = new Grafo(0,1,0,0);

    Lista<Vertice>* pilhaVertices = new Lista<Vertice>();
    pilhaVertices->insereInicio(inicio);

    while(!pilhaVertices->ehVazia())
    {
        Vertice* atual = pilhaVertices->desempilhaPrimeiro();
        Lista<Aresta>* arestas = atual->getArestas();
        arestas->imprimeLista();
        arestas->iterator = arestas->iteratorInicio();

        resultado->insereVertice(atual->getId());
        while(arestas->iterator != nullptr)
        {
            if(resultado->insereVertice(arestas->iterator->getData()->getDestino()->getId()))
            {
                resultado->insereAresta(atual->getId(),arestas->iterator->getData()->getDestino()->getId(), 1, false);
                pilhaVertices->insereInicio(arestas->iterator->getData()->getDestino());
            }
            else if(!arestas->iterator->getData()->getDestino()->comparaId(atual->getId()))
            {
                //resultado->insereAresta(atual->getId(),arestas->iterator->getDestino()->getId(), 1, true);
            }
            arestas->proximo();
        }
    }
    resultado->imprimirGraphviz("buscaEmLargura");
    return resultado;
}


bool Grafo::aux(Grafo* resultado, TabelaHash* visitados, Vertice*  inicio)
{
    Lista<Vertice>* pilhaDeVertices = new Lista<Vertice>();
    Lista<Vertice>* caminho = new Lista<Vertice>();
    pilhaDeVertices->insereInicio(inicio);

    while(!pilhaDeVertices->ehVazia())
    {
        Vertice* atual= pilhaDeVertices->desempilhaPrimeiro();
        caminho->insereInicio(atual);
        ///se existe na solução atual
        if(resultado->vertices->busca(atual->getId()) != nullptr)
        {
            cout << "adicione todo o caminho ah solução e retorna" << endl;
            ///adicione todo o caminho ah solução e retorna
            Vertice* destino = caminho->desempilhaPrimeiro();
            caminho->imprimeLista();
            while(!caminho->ehVazia())
            {
                Vertice* origem = caminho->desempilhaPrimeiro();
                resultado->insereVertice(origem->getId());
                destino = origem;
            }
            visitados->insere(atual->getId(), atual);

            delete caminho;
            delete pilhaDeVertices;
            return true;

        }
        else if(atual->getArestas()->ehVazia() || (visitados->busca(atual->getId()) != nullptr))
        {
            ///desempilha do caminho pois chegamos a um fim
            cout << "desempilha do caminho pois chegamos a um fim" << endl;
            caminho->desempilhaPrimeiro();
        }
        else
        {
            ///poe todas as adjacencias na pilha de execução
            cout << "poe todas as adjacencias na pilha de execução" << endl;
            cout << "Adjacencias" << endl;
            atual->getArestas()->iterator = atual->getArestas()->iteratorInicio();

            while(atual->getArestas()->iterator != nullptr)
            {
                Vertice* verticeDestino = atual->getArestas()->iterator->getData()->getDestino();
                bool naoVisitadoOuSolucao = visitados->busca(verticeDestino->getId()) == nullptr ||
                                            resultado->vertices->busca(verticeDestino->getId()) != nullptr;

                if( naoVisitadoOuSolucao && pilhaDeVertices->busca(atual->getArestas()->iterator->getData()->getDestino()->getId()) == nullptr)
                {
                    cout <<"inserindo" << endl;
                    atual->getArestas()->iterator->getData()->getDestino()->imprime();
                    pilhaDeVertices->insereInicio(atual->getArestas()->iterator->getData()->getDestino());
                }
                atual->getArestas()->proximo();
            }
        }

        visitados->insere(atual->getId(), atual);
        pilhaDeVertices->imprimeLista();
    }

    delete caminho;
    delete pilhaDeVertices;
    return false;
}

float Grafo::dijkstra(int id_origem,int id_destino, ofstream& output )
{
    limpaMarcacao();

    if (id_origem != id_destino)
    {
        Vertice *vertAtual = vertices->busca(id_origem);

        if (vertAtual == nullptr || vertices->busca(id_destino) == nullptr)
        {
            cout << "Vertice nao existe" << endl;
            return -1;
        }

        float *distancia = new float[ordem];

        //distancia minima da origem para um vertice

        int *visitado = new int[ordem]; //marca se um vertice foi visitado

        int *vertAdj = new int[ordem];
        //marca os vertices adjacentes

        for (int i = 0; i < ordem; i++)
        {
            distancia[i] = FLT_MAX;

            vertAdj[i] = -1;

            visitado[i] = -1;
        }

        distancia[vertAtual->getId()] = 0;

        Lista<Aresta> *arestasNoAtual;

        float caminhoTam; // peso do caminho atual

        while (vertAtual->getId() != id_destino)
        {

            for (int i = 0; i < ordem; i++)
            {
                vertAdj[i] = -1;
            }

            caminhoTam = distancia[vertAtual->getId()];

            visitado[vertAtual->getId()] = 1;

            arestasNoAtual = vertAtual->getArestas();

            arestasNoAtual->iterator = arestasNoAtual->iteratorInicio();

            while (arestasNoAtual->iterator != nullptr)
            {
                Aresta *a = arestasNoAtual->iterator->getData();

                int idVertAdj = a->getDestino()->getId();

                vertAdj[idVertAdj] = 1;

                if (distancia[idVertAdj] > caminhoTam + a->getPeso())
                {

                    distancia[idVertAdj] = caminhoTam + a->getPeso();

                }

                arestasNoAtual->proximo();

                int proxCaminho = INT_MAX;

                int proxID = -1;

                for (int i = 0; i < ordem; i++)
                {
                    if (vertAdj[i] == 1)
                    {
                        if (distancia[i] < proxCaminho && visitado[i] != 1)
                        {
                            proxCaminho = distancia[i];
                            proxID = i;
                        }
                    }
                }

                vertAtual = vertices->busca(proxID);

            }
        }
        caminhoTam = distancia[vertAtual->getId()];

        delete []distancia;

        delete []visitado;

        delete []vertAdj;

        return caminhoTam;
    }
    else
    {
        //nenhum caminho se a origem == destino
        return 0;

    }
}

Aresta* getArestaMenorPeso(Tupla * tupla)
{

    Lista<Aresta>* lista = tupla->destino->getArestas();

    cout << "Arestas canditadas" << endl;
    lista->imprimeLista();
    cout << "------------------" << endl;


    Aresta* menor = nullptr;
    float menorPeso = INT_MAX;

    lista->iterator = lista->iteratorInicio();
    while(lista->iterator != nullptr)
    {

        Aresta* aresta = (Aresta*)lista->iterator->getData();

        if(!(aresta->getDestino()->ehVisitado()) &&
            (aresta->getPeso() <= menorPeso) &&
            (tupla->capacidade_restante - aresta->getPeso() >= 0 ))
        {
            menor = ((Aresta*)lista->iterator->getData());
            menorPeso = menor->getPeso();
        }
        lista->proximo();
    }
    return menor;
}

Lista<Tupla>* getCandidatos(vector<Lista<Tupla>*>* rotas)
{
    Lista<Tupla>* canditados = new Lista<Tupla>();

    for (size_t i = 0; i < rotas->size(); ++i)
    {
        Lista<Tupla>* tuplas = rotas->at(i);
        Tupla* t = tuplas->visitaPrimeiro();

        Aresta* menorAresta = getArestaMenorPeso(t);

        if(menorAresta != nullptr)
        {
            Tupla* t = new Tupla();

            t->capacidade_restante = ((Tupla*)tuplas->visitaPrimeiro())->capacidade_restante - menorAresta->getDestino()->getPeso();
            t->destino = menorAresta->getDestino();
            t->peso = menorAresta->getPeso();;
            t->index_rota = i;
            t->verticeId = menorAresta->getDestino()->getId();

            canditados->insereInicio(t);
        }
    }
    return canditados;

}
Grafo* Grafo::algoritimoGulosoRoteamento(int numVeiculos, int id_origem)
{
    this->limpaMarcacao();
    Vertice*  origem = vertices->busca(id_origem);

    origem->setVisitado(true);

    vector<Lista<Tupla>*> rotas;
    rotas.resize(numVeiculos);

    //inicializando rotas
    for (size_t i = 0; i < rotas.size(); ++i)
    {
        rotas.at(i) = new Lista<Tupla>();

        Tupla* t = new Tupla();
        t->capacidade_restante = 100;
        t->destino = origem;
        t->peso = 0;
        t->index_rota = i;
        t->verticeId = origem->getId();

        ((Lista<Tupla>*)rotas.at(i))->insereInicio(t);
    }

    //começando iteração

    bool fim = false;

    do
    {
        Lista<Tupla>* canditatos = nullptr;
        canditatos = getCandidatos(&rotas);

        cout << "Canditatos-------" << endl;

        canditatos->iterator = canditatos->iteratorInicio();
        while(canditatos->iterator != nullptr)
        {
            cout<< " -" << canditatos->iterator->getData()->getId() << "(" << canditatos->iterator->getData()->getPeso() << ")- "<<"(" << canditatos->iterator->getData()->destino->getPeso() << ")";
            canditatos->proximo();
        }
        cout<< endl;
        cout << "-----------------" << endl;
        canditatos->iterator = canditatos->iteratorInicio();

        Tupla* melhor = nullptr;
        float melhorPeso = INT_MAX;

        //o melhor
        while(canditatos->iterator != nullptr)
        {
            if(melhorPeso > ((Tupla*)canditatos->iterator->getData())->peso)
            {
                melhor = ((Tupla*)canditatos->iterator->getData());
                melhorPeso = melhor->peso;
            }
            canditatos->proximo();
        }

        if(canditatos->ehVazia() || melhor == nullptr)
        {
            fim = true;
        }
        else
        {
            int rotaMelhor = melhor->index_rota;

            melhor->destino->setVisitado(true);
            ((Lista<Tupla>*)rotas.at(rotaMelhor))->insereInicio(melhor);

            for (size_t j = 0; j < rotas.size(); ++j)
            {
                cout << "[" << j <<"]";
                Lista<Tupla>* rotaimprime = rotas.at(j);
                rotaimprime->iterator = rotaimprime->iteratorInicio();
                while(rotaimprime->iterator != nullptr)
                {
                    cout<< " -" << rotaimprime->iterator->getData()->getId() << "(" << rotaimprime->iterator->getData()->getPeso() << ")" << "(" << rotaimprime->iterator->getData()->capacidade_restante << ")- ";
                    rotaimprime->proximo();
                }
                cout<< endl;
                rotaimprime->iterator = rotaimprime->iteratorInicio();

            }
            system("pause");
        }

        delete canditatos;

    }
    while(!fim);



}
