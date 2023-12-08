#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include <limits>
#include <regex>
#include <typeinfo>

#include "./includes/Grafo.h"
float INFINITO = 214748364 / 2;

using namespace std;

int menuManual()
{
    int escolha = -1;
    cout << "[menu]" << endl;
    cout << "(1)Inserir novo vertice" << endl;
    cout << "(2)Inserir nova aresta" << endl;
    cout << "(3)Remover vertice" << endl;
    cout << "(4)Remover aresta" << endl;
    cout << endl
         << "(-1)sair" << endl;

    cin >> escolha;

    // system("CLS");
    return escolha;
}
int menuAlgoritimos()
{
    int escolha;
    cout << "[menu algoritimos]" << endl;
    cout << "(1)Subgrafo vertice-induzido por feixo transitivo direto" << endl;
    cout << "(2)Subgrafo vertice-induzido por feixo transitivo indireto" << endl;
    cout << "(3)Caminho Minimo Djkstra" << endl;
    cout << "(4)Caminho Minimo floyd" << endl;
    cout << "(5)Arvore Geradora Minima - Prim" << endl;
    cout << "(6)Arvore Geradora Minima - Krusal" << endl;
    cout << "(7)Caminhamento em largura" << endl;
    cout << "(8)Ordenacao topoligica" << endl;
    cout << "(9)Algoritimo Guloso" << endl;
    cout << "(10)Algoritimo Guloso Randomizado" << endl;
    cout << "(11)Imprimir com Graphviz" << endl;
    cout << "(12)Mudancas Manuais" << endl;
    cout << endl
         << "(-1)Sair" << endl;
    cin >> escolha;
    return escolha;
}
void escolhasManuais(Grafo *g)
{
    bool exit = false;
    int escolha;
    do
    {
        int id_o;
        int id_d;
        float p;
        // g->TESTE_imprimeGrafo();
        system("CLS");
        escolha = menuManual();

        switch (escolha)
        {
        case 1:
            cout << "[INSERIR NOVO VERTICE]" << endl;
            cout << " informe o id do vertice" << endl;
            cin >> id_o;
            g->insereVertice(id_o, 1);
            break;
        case 2:
            cout << "[INSERIR NOVA ARESTA]" << endl;
            cout << "infome os ids de origem e destino respectivamente" << endl;
            cin >> id_o;
            cin >> id_d;
            cout << "informe o peso da aresta" << endl;
            cin >> p;
            g->insereAresta(id_o, id_d, p);
            break;
        case 3:
            cout << "[REMOVER VERTICE]" << endl;
            cout << " informe o id do vertice" << endl;
            cin >> id_o;
            g->removeVertice(id_o);
            break;
        case 4:
            cout << "[REMOVER ARESTA]" << endl;
            cout << "infome os ids de origem e destino respectivamente" << endl;
            cin >> id_o;
            cin >> id_d;
            g->removeAresta(id_o, id_d);
            break;
        case -1:
            exit = true;
            break;
        default:
            cout << "indice invalido" << endl;
            break;
        }
    } while (!exit);
}
void escolhasAlgoritimos(Grafo *g, ofstream &output, int repeticoes = 2500, int rotas = 5, int num_capacidade = 100)
{
    bool exit = false;
    int escolha;
    Grafo *saida = nullptr;
    do
    {
        int id_o;
        int id_d;
        system("CLS");
        escolha = menuAlgoritimos();

        switch (escolha)
        {
        case 1:
            cout << "[SUBGRAFO VERTICE INDUZIDO POR FEIXO TRANSITIVO DIRETO]" << endl;
            cout << "infome o id de origem" << endl;
            cin >> id_o;
            break;
        case 2:
            cout << "[SUBGRAFO VERTICE INDUZIDO POR FEIXO TRANSITIVO INDIRETO]" << endl;
            cout << "infome o id de busca" << endl;
            cin >> id_o;

            saida = g->SGVI_fechoTransitivoIndireto(id_o, output);
            break;
        case 3:
            cout << "[MENOR CAMINHO - DIJKSTRA]" << endl;
            cout << "infome os ids de origem e destino respectivamente" << endl;
            cin >> id_o;
            cin >> id_d;
            g->dijkstra(id_o, id_d, output);
            break;
        case 4:
            cout << "[MENOR CAMINHO - FLOYD]" << endl;
            cout << "infome os ids de origem e destino respectivamente" << endl;
            cin >> id_o;
            cin >> id_d;
            // g->floyd(id_o, id_d, output);
            break;
        case 5:
            cout << "[ARVORE GERADORA MINIMA - PRIM] " << endl;
            // g->agmPrim(output);
            break;
        case 6:
            cout << "[ARVORE GERADORA MINIMA - KRUSKAL]" << endl;
            // g->agmKruskal(output);
            break;
        case 7:
            cout << "[BUSCA EM LARGURA]" << endl;
            cout << "infome o id de inicio" << endl;
            cin >> id_o;
            saida = g->buscaEmLargura(id_o);
            break;
        case 8:
            cout << "[ORDENA��O TOPOLOGICA]" << endl;
            cout << "infome o id de inicio" << endl;
            cin >> id_o;
            break;
        case 9:
            cout << "[Algoritimo Guloso]" << endl;
            g->algoritimoGulosoRoteamento(rotas, num_capacidade, 1 );
            break;
        case 10:
            cout << "[Algoritimo Guloso Randomizado]" << endl;
            g->algoritimoReativoRandomizadoGulosoRoteamento(rotas, num_capacidade, 1, repeticoes);
            break;
        case 11:
            cout << "[Impressão Graphviz]" << endl;
            g->imprimirGraphviz("grafo");
            break;
        case 12:
            escolhasManuais(g);
            break;
        case -1:
            exit = true;
            break;
        default:
            cout << "indice invalido" << endl;
            break;
        }

        // if(saida != nullptr) delete saida;
        // so pra n�o deixar os grafos criados perdidos em memoria
    } while (!exit);
}
Grafo *leituraPorAraquivo(ifstream &input_file, int directed, int weightedEdge, int weightedNode, string nome)
{
    float peso_vertice_o = 1;
    float peso_vertice_d = 1;
    float peso_aresta = 1;
    float ordem;
    int id_o;
    int id_d;

    input_file >> ordem;
    Grafo *g = new Grafo(directed, weightedEdge, weightedNode, nome);

    if (g->temPesoAresta() && g->temPesoVertice())
    {
        while (input_file >> id_o >> peso_vertice_o >> id_d >> peso_vertice_d >> peso_aresta)
        {
            g->insereVertice(id_o, peso_vertice_o);
            cout << "inserendo vertice " << id_o << "de peso " << peso_vertice_o << endl;
            g->insereVertice(id_d, peso_vertice_d);
            cout << "inserendo vertice " << id_d << "de peso " << peso_vertice_d << endl;
            g->insereAresta(id_o, id_d, peso_aresta);
            cout << "inserindo arestas entre " << id_o << " e " << id_d << " de peso " << peso_aresta << endl;
        }
    }
    else if (g->temPesoAresta())
    {
        while (input_file >> id_o >> id_d >> peso_aresta)
        {
            g->insereVertice(id_o, peso_vertice_o);
            cout << "inserendo vertice " << id_o << " de peso " << peso_vertice_o << endl;
            g->insereVertice(id_d, peso_vertice_d);
            cout << "inserendo vertice " << id_d << " de peso " << peso_vertice_d << endl;
            g->insereAresta(id_o, id_d, peso_aresta);
            cout << "inserindo arestas entre " << id_o << " e " << id_d << " de peso " << peso_aresta << endl;
        }
    }
    else if (g->temPesoVertice())
    {
        while (input_file >> id_o >> peso_vertice_o >> id_d >> peso_vertice_d)
        {
            g->insereVertice(id_o, peso_vertice_o);
            cout << "inserendo vertice " << id_o << " de peso " << peso_vertice_o << endl;
            g->insereVertice(id_d, peso_vertice_d);
            cout << "inserendo vertice " << id_d << " de peso " << peso_vertice_d << endl;
            g->insereAresta(id_o, id_d, peso_aresta);
            cout << "inserindo arestas entre " << id_o << " e " << id_d << " de peso " << peso_aresta << endl;
        }
    }
    else
    {
        while (input_file >> id_o >> id_d)
        {
            g->insereVertice(id_o, peso_vertice_o);
            cout << "inserendo vertice " << id_o << " de peso " << peso_vertice_o << endl;
            g->insereVertice(id_d, peso_vertice_d);
            cout << "inserendo vertice " << id_d << " de peso " << peso_vertice_d << endl;
            g->insereAresta(id_o, id_d, peso_aresta);
            cout << "inserindo arestas entre " << id_o << " e " << id_d << " de peso " << peso_aresta << endl;
        }
    }

    return g;
}

Grafo *leituraPorAraquivoTipo2(ifstream &input_file, string nome, int *num_rotas, int *num_capacidade)
{
    bool leitura_coords = false, leitura_demanda = false;
    std::string linha;
    int capacidade = 0, coordId = 0, coordX = 0, coordY = 0, coordDemanda = 0;

    Grafo *g = new Grafo(0, 1, 1, nome);

    bool achouCapacidade = false;
    bool achouNCaminhoes = false;

    if (input_file.is_open())
    {
        std::regex padraoCaminha0("(No of trucks): (\\d+)"); // Expressão regular para encontrar o padrão "No of trucks: número"
        std::regex padraoCapacidade("CAPACITY : (\\d+)");    // Expressão regular para encontrar o padrão "CAPACITY: número"

        while (std::getline(input_file, linha))
        {
            std::stringstream iss(linha);

            std::smatch matches;

            
            if (std::regex_search(linha, matches, padraoCaminha0) && !achouNCaminhoes)
            {
                if (matches.size() == 3)
                {
                    std::string info = matches[2];           // O número de caminhões está no segundo grupo capturado pela expressão regular
                    int numeroDeCaminhoes = std::stoi(info); // Convertendo a string para um número inteiro
                    *num_rotas = numeroDeCaminhoes;
                }
            }

            if (std::regex_search(linha, matches, padraoCapacidade)&& !achouCapacidade)
            {
                if (matches.size() == 2)
                {
                    std::string info = matches[1];         // O valor da capacidade está no primeiro grupo capturado pela expressão regular
                    *num_capacidade = std::stoi(info); // Convertendo a string para um número inteiro
                }
            }

            if (linha.find("NODE_COORD_SECTION") != std::string::npos)
            {
                leitura_coords = true;
                leitura_demanda = false;
                continue;
            }

            if (linha.find("DEMAND_SECTION") != std::string::npos)
            {
                leitura_coords = false;
                leitura_demanda = true;
                continue;
            }

            if (linha.find("DEPOT_SECTIO") != std::string::npos)
            {
                leitura_coords = false;
                leitura_demanda = false;
                continue;
            }

            if (leitura_coords)
            {
                iss >> coordId >> coordX >> coordY;
                g->insereVertice(coordId, 1, coordX, coordY);
            }

            if (leitura_demanda)
            {
                iss >> coordId >> coordDemanda;
                // cout << "coordId " << coordId << " coordDemanda " << coordDemanda << endl;
                g->getVertice(coordId)->setPeso(coordDemanda);
                // system("pause");
            }
        }
        g->geraDistanciasDeVertices();
        input_file.close();
    }
    else
    {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
    }
    return g;
}
// Função para validar se todos os argumentos esperados foram fornecidos
bool validarArgumentos(int argc)
{
    // Verifica se a quantidade mínima de argumentos foi passada
    if (argc < 4 || argc > 7)
    {
        std::cout << "Uso: ./<program_name> <type> <input_file> <output_file> [<directed> <weighted_edge> <weighted_node>]" << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    // Verifica se a quantidade de argumentos é válida
    if (!validarArgumentos(argc))
    {
        return 1;
    }

    // Armazena os argumentos da linha de comando em variáveis
    std::string program_name = argv[0];
    std::string type = argv[1];
    std::string input_file_name = argv[2];
    std::string output_file_name = argv[3];

    string instance;
    if (input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    // Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(input_file_name, ios::in);
    output_file.open(output_file_name, ios::out | ios::app);

    Grafo *graph;

    if (input_file.is_open())
    {
        if (argc == 7 && type == "1")
        {
            size_t pos = input_file_name.find('/');
            string nomeSemPath = input_file_name.substr(pos + 1);
            pos = input_file_name.find('.');
            string nome = nomeSemPath.substr(0, pos);

            graph = leituraPorAraquivo(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), nome);
            escolhasAlgoritimos(graph, output_file);
        }
        else if (argc == 5 && type == "2")
        {
            size_t pos = input_file_name.find('/');
            string nomeSemPath = input_file_name.substr(pos + 1);
            pos = input_file_name.find('.');
            string nome = nomeSemPath.substr(0, pos);

            int num_rotas = 0;
            int num_capacidade = 0;

            graph = leituraPorAraquivoTipo2(input_file, nome, &num_rotas, &num_capacidade);

            escolhasAlgoritimos(graph, output_file, atoi(argv[4]), num_rotas, num_capacidade);
        }
    }
    else
        cout << "Unable to open " << argv[2];

    return 0;
}
