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
    cout << "(8)Ordena��o topoligica" << endl;
    cout << "(9)Mudancas manuais" << endl;
    cout << "(10)Imprimir com Graphviz" << endl;
    cout << "(11)Algoritimo Guloso" << endl;
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
    }
    while (!exit);
}
void escolhasAlgoritimos(Grafo *g, ofstream &output)
{
    bool exit = false;
    int escolha;
    Grafo *saida = nullptr;
    do
    {
        int id_o;
        int id_d;
        // g->TESTE_imprimeGrafo();
        system("CLS");
        escolha = menuAlgoritimos();

        switch (escolha)
        {
        case 1:
            cout << "[SUBGRAFO VERTICE INDUZIDO POR FEIXO TRANSITIVO DIRETO]" << endl;
            cout << "infome o id de origem" << endl;
            cin >> id_o;
            //saida = g->SGVI_feixoTransitivoDireto(id_o, output);
            // cout << "[TESTE]" << endl << endl;
            // saida->TESTE_imprimeGrafo();

            break;
        case 2:
            cout << "[SUBGRAFO VERTICE INDUZIDO POR FEIXO TRANSITIVO INDIRETO]" << endl;
            cout << "infome o id de busca" << endl;
            cin >> id_o;

            saida = g->SGVI_fechoTransitivoIndireto(id_o, output);

            //cout << "[TESTE]" << endl << endl;
            //saida->TESTE_imprimeGrafo();

            break;
        case 3:
            cout << "[MENOR CAMINHO - DIJKSTRA]" << endl;
            cout << "infome os ids de origem e destino respectivamente" << endl;
            cin >> id_o;
            cin >> id_d;
            //g->dijkstra(id_o, id_d, output);
            break;
        case 4:
            cout << "[MENOR CAMINHO - FLOYD]" << endl;
            cout << "infome os ids de origem e destino respectivamente" << endl;
            cin >> id_o;
            cin >> id_d;
            //g->floyd(id_o, id_d, output);
            break;
        case 5:
            cout << "[ARVORE GERADORA MINIMA - PRIM] " << endl;
            //            //cout << "criando grafo manualmente..." << endl;
            //            Grafo* f = new Grafo(0 , 0  , 1 , 0);
            //            escolhasManuais(f);
            //            f->agmPrim();

            //g->agmPrim(output);
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
            escolhasManuais(g);
            break;

        case 10:
            cout << "[Impressão Graphviz]" << endl;
            g->imprimirGraphviz("grafo");
            break;

        case 11:
            cout << "[Algoritimo Guloso]" << endl;
            g->algoritimoGulosoRoteamento(5, 1, 0.4);
            break;
        case 12:
            cout << "[Algoritimo Guloso]" << endl;
            g->algoritimoReativoRandomizadoGulosoRoteamento(5, 1, 2500);
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
    }
    while (!exit);
}
Grafo *leituraPorAraquivo(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{
    float peso_vertice_o = 1;
    float peso_vertice_d = 1;
    float peso_aresta = 1;
    float ordem;
    int id_o;
    int id_d;

    input_file >> ordem;
    Grafo *g = new Grafo(0, directed, weightedEdge, weightedNode);

    if (g->temPesoAresta() && g->temPesoVertice())
    {
        while (input_file >> id_o >> peso_vertice_o >> id_d >> peso_vertice_d >> peso_aresta)
        {
            cout << "salve 2" << endl;
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
            cout << "salve 3" << endl;
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
            cout << "salve 4" << endl;
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
            cout << "salve" << endl;
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

Grafo *leituraPorAraquivoTipo2(ifstream &input_file)
{
    bool leitura_coords = false, leitura_demanda = false;
    std::string linha;
    int capacidade = 0, coordId = 0, coordX = 0,coordY = 0, coordDemanda = 0;

    Grafo* g = new Grafo(0,0,1,1);

    if (input_file.is_open())
    {
        while (std::getline(input_file, linha))
        {
            std::stringstream iss(linha);

            if (linha.find("CAPACITY") != std::string::npos)
            {
                std::stringstream cap_stream(linha);
                std::string token;
                while (cap_stream >> token)
                {
                    if (token == "CAPACITY")
                    {
                        cap_stream >> capacidade;
                        break;
                    }
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
                //cout << "coordId " << coordId << " coordDemanda " << coordDemanda << endl;
                g->getVertice(coordId)->setPeso(coordDemanda);
                //system("pause");
            }

        }
        g->geraDistanciasDeVertices();
        input_file.close();
    }
    else
    {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
    }

    system("pause");

    return g;
}

int main()
{
    ifstream input;
    ofstream output_file;
    output_file.open("TESTEOut", ios::out | ios::trunc);
    input.open("inputs/grafo_teste.txt", ios::in);
    if(input.is_open())
    {
        Grafo * xd = leituraPorAraquivoTipo2(input);
        escolhasAlgoritimos(xd, output_file);
    }
    input.close();
    return 0;
}

//int main(int argc, char const *argv[])
//{
//    /*
//        //Verifica��o se todos os par�metros do programa foram entrados
//        if (argc != 6) {
//
//            cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
//            return 1;
//
//        }
//
//        string program_name(argv[0]);
//        string input_file_name(argv[1]);
//
//        string instance;
//        if(input_file_name.find("v") <= input_file_name.size()){
//            string instance = input_file_name.substr(input_file_name.find("v"));
//            cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
//        }
//
//        //Abrindo arquivo de entrada
//        ifstream input_file;
//        ofstream output_file;
//        input_file.open(argv[1], ios::in);
//        output_file.open(argv[2], ios::out | ios::trunc);
//
//        Grafo* graph;
//
//        if(input_file.is_open()){
//
//            graph = leituraPorAraquivo(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
//
//        }else
//            cout << "Unable to open " << argv[1];
//
//    */
//
//    //Abrindo arquivo de entrada
//    ifstream input_file;
//    ofstream output_file;
//    input_file.open("teste", ios::in);
//    output_file.open("TESTEOut", ios::out | ios::trunc);
//
//    Grafo *grafo = new Grafo(1, 0, 0, 0);
//    escolhasAlgoritimos(grafo, output_file);
//
//    return 0;
//}

/*
int main(int argc, char const *argv[])
{


        //Verifica��o se todos os par�metros do programa foram entrados
        if (argc != 6) {

            cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
            return 1;

        }

        string program_name(argv[0]);
        string input_file_name(argv[1]);

        string instance;
        if(input_file_name.find("v") <= input_file_name.size()){
            string instance = input_file_name.substr(input_file_name.find("v"));
            cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
        }

        //Abrindo arquivo de entrada
        ifstream input_file;
        ofstream output_file;
        input_file.open(argv[1], ios::in);
        output_file.open(argv[2], ios::out | ios::trunc);

        Grafo* graph;

        if(input_file.is_open()){

            graph = leituraPorAraquivo(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

        }else
            cout << "Unable to open " << argv[1];



    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open("grafo_125.txt", ios::in);
    output_file.open("TESTEOut", ios::out | ios::trunc);

    Grafo *grafo = new Grafo(1, 0, 0, 0);
    escolhasAlgoritimos(grafo, output_file);

    return 0;
}

*/


