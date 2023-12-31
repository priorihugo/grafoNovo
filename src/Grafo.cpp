#define INT_MAX 2147483640 / 2
#define FLT_MAX 2147483640 / 2
#include "../includes/Grafo.h"

Grafo::Grafo(int temDirecao, int temPesoAresta, int temPesoVertice, string nome)
{
    eh_direcionado = temDirecao == 1 ? true : false;
    tem_peso_aresta = temPesoAresta == 1 ? true : false;
    tem_peso_vertice = temPesoVertice == 1 ? true : false;

    this->nome = nome;

    this->vertices = new TabelaHash(10);
}
Grafo::~Grafo()
{
    delete vertices;
}

bool Grafo::insereVertice(int id_origem, float peso = 1, int coordX, int coordY)
{
    if (vertices->busca(id_origem) == nullptr)
    {
        vertices->insere(id_origem, new Vertice(id_origem, peso, coordX, coordY));
        ordem++;
        return true;
    }

    return false;
}
void Grafo::removeVertice(int id_origem)
{
    Vertice *v = vertices->busca(id_origem);
    // lembrar de decrementar o grau de entrada de todo vertice atingido e remover as arestas
    // que incidem sober o vertice a ser deletado
    if (v != nullptr)
    {
        Lista<Aresta> *lista = v->getArestas();
        lista->iterator = lista->iteratorInicio();

        // precisamos ir onde cada aresta incide e deletar conexões com este vertice
        while (lista->iterator != nullptr)
        {
            lista->iterator->getData()->getDestino()->decEntrada();
            lista->iterator->getData()->getDestino()->removeAresta(id_origem);

            lista->proximo();
        }
        vertices->remove(id_origem);
        ordem--;
    }
}
bool Grafo::insereAresta(int id_origem, int id_destino, float peso, bool ehRetorno)
{
    // cout << "inserindo aresta origem: " << id_origem << " destino " << id_destino << endl;
    Vertice *origem = vertices->busca(id_origem);
    Vertice *destino = vertices->busca(id_destino);

    if (origem != nullptr && destino != nullptr)
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

    if (origem != nullptr && destino != nullptr)
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

Vertice *Grafo::getVertice(int id)
{
    return this->vertices->busca(id);
}

void Grafo::geraDistanciasDeVertices()
{
    limpaMarcacao();

    float distancia = 0;
    // vertices->imprimeComoTabela();
    vertices->iterator = vertices->iteratorInicio();
    No<Vertice> *atual = vertices->iterator;

    while (vertices->iterator != nullptr)
    {
        atual = vertices->iterator;
        No<Vertice> *iteracao = vertices->iterator = vertices->iteratorInicio();

        while (iteracao != nullptr)
        {
            if (atual->getData()->getId() != iteracao->getData()->getId())
            {
                Vertice *dataI = iteracao->getData();
                Vertice *dataA = atual->getData();

                float quadradoX = pow(abs(dataI->getX() - dataA->getX()), 2);
                float quadradoY = pow(abs(dataI->getY() - dataA->getY()), 2);

                distancia = sqrt(quadradoX + quadradoY);
                this->insereAresta(dataA->getId(), dataI->getId(), distancia, false);
            }
            iteracao = vertices->proximo();
        }

        vertices->setIterator(atual);
        vertices->proximo();
    }
}

void Grafo::limpaMarcacao()
{

    vertices->iterator = vertices->iteratorInicio();
    while (vertices->iterator != nullptr)
    {
        Vertice *v = vertices->iterator->getData();
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

    std::string colors[] =
        {
            "red", "green", "blue", "yellow", "purple", "orange",
            "black", "white", "pink", "cyan", "brown", "gold",
            "silver", "gray", "lime green", "aqua"};

    cout << "Abrindo o arquivo " << endl;

    if (output.is_open())
    {
        string conector;
        if (this->direcionado())
        {
            /// inserindo no output um grafo direcionado
            output << "digraph " << nome << " {" << endl;
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
            if (lista->iterator == nullptr)
            {
                output << vertices->iterator->getData()->getId() << endl;
            }
            else
            {
                while (lista->iterator != nullptr)
                {
                    Aresta *a = lista->iterator->getData();
                    output << vertices->iterator->getData()->getId() << conector << a->getDestino()->getId();

                    // if(a->ehArestaRetorno()) output << " [ color=\"red\" ]";

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
}

Grafo *Grafo::SGVI_fechoTransitivoIndireto(int id_origem, ofstream &output)
{
    limpaMarcacao();

    int index = 0;

    Grafo *resultado = new Grafo(1, 0, 0);
    Vertice *verticeInicio = this->vertices->busca(id_origem);
    TabelaHash *visitados = new TabelaHash(2);

    if (verticeInicio == nullptr)
        return nullptr;

    resultado->insereVertice(verticeInicio->getId(), verticeInicio->getPeso());

    /// iterando todos os vertices do grafo atual
    this->vertices->iterator = this->vertices->iteratorInicio();
    while (this->vertices->iterator != nullptr)
    {
        aux(resultado, visitados, this->vertices->iterator->getData());
        this->vertices->proximo();
        index++;
    }

    string out = this->nome;
    out.append("_FTI");

    resultado->imprimirGraphviz(out);
    return resultado;
}

Grafo *Grafo::buscaEmLargura(int id)
{
    limpaMarcacao();

    Vertice *inicio = this->vertices->busca(id);
    Grafo *resultado = new Grafo(1, 0, 0);

    Lista<Vertice> *pilhaVertices = new Lista<Vertice>();
    pilhaVertices->insereInicio(inicio);

    while (!pilhaVertices->ehVazia())
    {
        Vertice *atual = pilhaVertices->desempilhaPrimeiro();
        Lista<Aresta> *arestas = atual->getArestas();
        // arestas->imprimeLista();
        arestas->iterator = arestas->iteratorInicio();

        resultado->insereVertice(atual->getId());
        while (arestas->iterator != nullptr)
        {
            if (resultado->insereVertice(arestas->iterator->getData()->getDestino()->getId()))
            {
                resultado->insereAresta(atual->getId(), arestas->iterator->getData()->getDestino()->getId(), 1, false);
                pilhaVertices->insereInicio(arestas->iterator->getData()->getDestino());
            }
            else if (!arestas->iterator->getData()->getDestino()->comparaId(atual->getId()))
            {
                // resultado->insereAresta(atual->getId(),arestas->iterator->getDestino()->getId(), 1, true);
            }
            arestas->proximo();
        }
    }
    resultado->imprimirGraphviz("buscaEmLargura");
    return resultado;
}

bool Grafo::aux(Grafo *resultado, TabelaHash *visitados, Vertice *inicio)
{
    Lista<Vertice> *pilhaDeVertices = new Lista<Vertice>();
    Lista<Vertice> *caminho = new Lista<Vertice>();
    pilhaDeVertices->insereInicio(inicio);

    while (!pilhaDeVertices->ehVazia())
    {
        Vertice *atual = pilhaDeVertices->desempilhaPrimeiro();
        caminho->insereInicio(atual);
        /// se existe na solução atual
        if (resultado->vertices->busca(atual->getId()) != nullptr)
        {
            cout << "adicione todo o caminho ah solução e retorna" << endl;
            /// adicione todo o caminho ah solução e retorna
            Vertice *destino = caminho->desempilhaPrimeiro();
            // caminho->imprimeLista();
            while (!caminho->ehVazia())
            {
                Vertice *origem = caminho->desempilhaPrimeiro();
                resultado->insereVertice(origem->getId());
                destino = origem;
            }
            visitados->insere(atual->getId(), atual);

            delete caminho;
            delete pilhaDeVertices;
            return true;
        }
        else if (atual->getArestas()->ehVazia() || (visitados->busca(atual->getId()) != nullptr))
        {
            /// desempilha do caminho pois chegamos a um fim
            cout << "desempilha do caminho pois chegamos a um fim" << endl;
            caminho->desempilhaPrimeiro();
        }
        else
        {
            /// poe todas as adjacencias na pilha de execução
            cout << "poe todas as adjacencias na pilha de execução" << endl;
            cout << "Adjacencias" << endl;
            atual->getArestas()->iterator = atual->getArestas()->iteratorInicio();

            while (atual->getArestas()->iterator != nullptr)
            {
                Vertice *verticeDestino = atual->getArestas()->iterator->getData()->getDestino();
                bool naoVisitadoOuSolucao = visitados->busca(verticeDestino->getId()) == nullptr ||
                                            resultado->vertices->busca(verticeDestino->getId()) != nullptr;

                if (naoVisitadoOuSolucao && pilhaDeVertices->busca(atual->getArestas()->iterator->getData()->getDestino()->getId()) == nullptr)
                {
                    cout << "inserindo" << endl;
                    // atual->getArestas()->iterator->getData()->getDestino()->imprime();
                    pilhaDeVertices->insereInicio(atual->getArestas()->iterator->getData()->getDestino());
                }
                atual->getArestas()->proximo();
            }
        }

        visitados->insere(atual->getId(), atual);
        // pilhaDeVertices->imprimeLista();
    }

    delete caminho;
    delete pilhaDeVertices;
    return false;
}

float Grafo::dijkstra(int id_origem, int id_destino, ofstream &output)
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

        // distancia minima da origem para um vertice

        int *visitado = new int[ordem]; // marca se um vertice foi visitado

        int *vertAdj = new int[ordem];
        // marca os vertices adjacentes

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

        delete[] distancia;

        delete[] visitado;

        delete[] vertAdj;

        return caminhoTam;
    }
    else
    {
        // nenhum caminho se a origem == destino
        return 0;
    }
}

Aresta *getArestaMenorPeso(Rota *rota , int id_origem)
{
    Lista<Aresta> *lista = rota->getPonta()->destino->getArestas();
    Aresta *menor = nullptr;
    float menorPeso = INT_MAX;
    float porcentagemCheio = rota->getPorcentagemParaVolta();
    float limiteDistancia = rota->getThreshold();

    //busca uma aresta proxima a origem;
    if (rota->getCapacidadeRestante() > rota->getCapacidadeMaxima() * porcentagemCheio)
    {
        lista->iterator = lista->iteratorInicio();
        while (lista->iterator != nullptr)
        {
            Aresta *aresta = (Aresta *)lista->iterator->getData();
            Vertice* verticeCandidato = aresta->getDestino();
            Aresta* distanciaParaOrigem = verticeCandidato->buscaAresta(id_origem);

            if (!(verticeCandidato->ehVisitado()) &&
                (aresta->getPeso() <= menorPeso) &&
                (distanciaParaOrigem->getPeso() <= limiteDistancia) &&
                (rota->getPonta()->capacidade_restante - verticeCandidato->getPeso() >= 0))
            {
                menor = aresta;
                menorPeso = menor->getPeso();
            }
            lista->proximo();
        }
    }

    if(menor != nullptr) return menor;
    
    //busca uma aresta no geral
    lista->iterator = lista->iteratorInicio();
    while (lista->iterator != nullptr)
    {
        Aresta *aresta = (Aresta *)lista->iterator->getData();

        if (!(aresta->getDestino()->ehVisitado()) &&
            (aresta->getPeso() <= menorPeso) &&
            (rota->getPonta()->capacidade_restante - aresta->getDestino()->getPeso() >= 0))
        {
            menor = ((Aresta *)lista->iterator->getData());
            menorPeso = menor->getPeso();
        }
        lista->proximo();
    }
    return menor;
}

// Função de particionamento para o Quicksort
int particionar(std::vector<Tupla *> &vetor, int baixo, int alto)
{
    int pivo = vetor[alto]->getPeso();
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++)
    {
        if (vetor[j]->getPeso() < pivo)
        {
            i++;
            std::swap(vetor[i], vetor[j]);
        }
    }
    std::swap(vetor[i + 1], vetor[alto]);
    return (i + 1);
}

// Função Quicksort
void quicksort(std::vector<Tupla *> &vetor, int baixo, int alto)
{
    if (baixo < alto)
    {
        int pi = particionar(vetor, baixo, alto);

        quicksort(vetor, baixo, pi - 1);
        quicksort(vetor, pi + 1, alto);
    }
}

vector<Tupla *> *getCandidatos(Solucao *rotas, int tamanho , int id_origem)
{
    //    cout << "todas as rotas " << endl;
    //    rotas->imprime();
    //    cout << "-------------- " << endl;

    vector<Tupla *> *canditados = new vector<Tupla *>();
    for (size_t i = 0; i < tamanho; ++i)
    {
        Tupla *tuplaPonta = rotas->getRota(i)->getPonta();
        Aresta *menorAresta = getArestaMenorPeso(rotas->getRota(i) , id_origem);

        if (menorAresta != nullptr)
        {
            Tupla *t = new Tupla();
            t->capacidade_restante = tuplaPonta->capacidade_restante - menorAresta->getDestino()->getPeso();
            t->destino = menorAresta->getDestino();
            t->peso = menorAresta->getPeso();
            t->index_rota = i;
            t->verticeId = menorAresta->getDestino()->getId();

            //            cout <<"menor aresta inserida nos candidatos "<< endl;
            //            t->imprime();
            //            cout<<"--------------------------------------"<< endl;
            canditados->push_back(t);
        }
    }

    // printVector<Tupla*>(canditados);
    quicksort(*canditados, 0, (int)(canditados->size() - 1));
    // printVector<Tupla*>(canditados);

    return canditados;
}

void atualizaProbabilidades(double probabilidades[], double medias[], double melhor, int tamanho)
{
    double qualidadeTotal = 0;
    double qualidades[6];

    for (size_t i = 0; i < tamanho; i++)
    {
        if (medias[i] > 0)
        {
            qualidades[i] = melhor / medias[i];
            qualidadeTotal += qualidades[i];
        }
    }

    for (size_t i = 0; i < tamanho; i++)
    {
        probabilidades[i] = qualidades[i] / qualidadeTotal;
    }

    // cout << "probabilidades" << endl;
    // for (size_t i = 0; i < tamanho; i++)
    // {
    //     cout << "[" << i << "] " << probabilidades[i] << endl;
    //     ;
    // }
    // cout << endl;
}

int escolheIndiceAlpha(double probabilidades[], int tamanho)
{
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_real_distribution<double> dis(0.0, 1.0);
    double randomNumber = dis(gen);
    float acumulador = 0;

    for (size_t i = 0; i < tamanho; i++)
    {
        acumulador = acumulador + probabilidades[i];

        if (acumulador >= randomNumber)
            return i;
    }

    return tamanho - 1;
}

void Grafo::algoritimoReativoRandomizadoGulosoRoteamento(int numVeiculos, int capacidade, int id_origem, int repeticoes)
{
    auto start = std::chrono::high_resolution_clock::now();
    // double alphas[6] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6};
    double alphas[6] = {0.05, 0.1, 0.15, 0.2, 0.25, 0.3};

    double probabilidades[6];
    double utilizados[6];

    for (size_t i = 0; i < 6; i++)
    {
        utilizados[i] = 0;
        probabilidades[i] = 1 / 6;
    }

    size_t limite = 100;
    size_t count = 0;

    Solucao *melhor = algoritimoGulosoRoteamento(numVeiculos, capacidade, id_origem, 0);
    // caso não encontre uma solução base, tente 100 vezes com radomizado
    while (melhor == nullptr && count == limite)
    {
        melhor = algoritimoGulosoRoteamento(numVeiculos, capacidade, id_origem, 0.5);
    };

    if (melhor == nullptr)
    {
        cout << "Não foi possivel encontrar uma solução base para o problema" << endl;
        return;
    }

    float melhorAlpha = 0;
    int num_erros = 0;

    double medias[6];
    double qualidades[6];

    for (size_t i = 0; i < 6; i++)
    {
        medias[i] = melhor->getQualidade();
        qualidades[i] = 0;
    }

    for (size_t i = 0; i < repeticoes; i++)
    {
        int alphaIndex = escolheIndiceAlpha(probabilidades, 6);
        utilizados[alphaIndex]++;

        Solucao *s = algoritimoGulosoRoteamento(numVeiculos, capacidade, id_origem, alphas[alphaIndex]);

        if (s != nullptr)
        {
            if (utilizados[alphaIndex] > 0)
            {
                qualidades[alphaIndex] += s->getQualidade();
                medias[alphaIndex] = qualidades[alphaIndex] / utilizados[alphaIndex];
            }

            if (melhor->getQualidade() > s->getQualidade())
            {
                melhor = s;
                melhorAlpha = alphas[alphaIndex];
            }

            atualizaProbabilidades(probabilidades, medias, melhor->getQualidade(), 6);
        }
        else
        {
            num_erros++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    cout << "melhor " << endl;
    melhor->imprime();

    std::chrono::duration<double> elapsed_seconds = end - start;

    // Imprimir a diferença de tempo

    ofstream output;
    string path = "output/";
    path = path.append(this->nome);
    path = path.append("_relatorio.txt");
    output.open(path, ios::app);

    cout << "path: " << path << endl;

    if (output.is_open())
    {
        output << "----------------------------------------" << endl;
        output << endl;
        output << "Nome: " << this->nome << endl;
        output << "repetições: " << repeticoes << endl;
        output << "Melhor Alpha: " << melhorAlpha << endl;
        output << "Tentativas sem solução viavel " << num_erros << endl;
        output << "Tempo decorrido: " << elapsed_seconds.count() << " segundos" << std::endl
               << endl;
        output << "Rota: " << endl;
        output << melhor->getParaTXT() << endl;
        output << "----------------------------------------" << endl
               << endl;
    }
    output.close();
}

Solucao *Grafo::algoritimoGulosoRoteamento(int numVeiculos, int capacidade, int id_origem, float alpha)
{
    this->limpaMarcacao();

    // this->vertices->imprimeComoTabela();
    Vertice *origem = vertices->busca(id_origem);
    origem->setVisitado(true);

    Solucao *sol = new Solucao(numVeiculos, capacidade);
    // inicializando rotas
    for (size_t i = 0; i < numVeiculos; ++i)
    {
        Tupla *t = new Tupla();
        t->capacidade_restante = capacidade;
        t->destino = origem;
        t->peso = 0;
        t->index_rota = i;
        t->verticeId = origem->getId();

        sol->getRota(i)->insere(t);
    }
    // começando iteração
    bool fim = false;
    do
    {
        vector<Tupla *> *canditatos = nullptr;
        canditatos = getCandidatos(sol, numVeiculos , id_origem);

        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        mt19937 gen(seed);
        uniform_real_distribution<double> dis(0.0, 1.0);
        double randomNumber = dis(gen);
        int indiceEscolhido = floor((canditatos->size() - 1) * alpha * randomNumber);

        if (canditatos->empty())
        {
            fim = true;
        }
        else
        {
            Tupla *melhor = canditatos->at(indiceEscolhido);
            int rotaMelhor = melhor->index_rota;
            melhor->destino->setVisitado(true);
            sol->getRota(rotaMelhor)->insere(melhor);

            // sol->imprime();
        }

        delete canditatos;
    } while (!fim);

    vertices->iterator = vertices->iteratorInicio();
    while (vertices->iterator != nullptr)
    {
        if (!vertices->iterator->getData()->ehVisitado())
            return nullptr;

        vertices->proximo();
    }

    for (size_t i = 0; i < numVeiculos; i++)
    {

        Tupla *t = sol->getRota(i)->getPonta();
        Aresta *a = t->destino->getArestas()->busca(id_origem);

        Tupla *volta = new Tupla();

        volta->destino = vertices->busca(id_origem);
        volta->verticeId = id_origem;
        volta->index_rota = t->index_rota;
        volta->capacidade_restante = t->capacidade_restante;
        volta->peso = a->getPeso();

        sol->getRota(i)->insere(volta);
    }

    return sol;
}
