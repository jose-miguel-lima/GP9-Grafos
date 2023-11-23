// #include <iostream>
// #include "No.h"
// #include "Grafo.h"

// using namespace std;

// int main(){

//     Grafo* grafo = new Grafo(0, true, true, false);
//     grafo->insereNo(0);
//     grafo->insereNo(1);
//     grafo->insereNo(2);

//     for(int i = 0; i < 3; i++){
//         for(int j = 0; j < 3; j++){
//             if(i !=j )
//                 grafo->insereAresta(i, j, 2);
//         }
//     }
    
//     grafo->printGraph();
    
//     grafo->preencheMatrizPesos();

//     cout << endl << "Matriz de pesos : " << endl;
//     for(int i = 0; i < 3; i++){
//         for(int j = 0; j < 3; j++){
//             cout << grafo->matrizPesos[i][j] << "     ";
//         }
//         cout << endl;
//     }
    


    /* ///TESTE DE distanciaMinima()
    Grafo* grafo = new Grafo(0, true, true, false);

    for(int i = 0; i <= 5; i++)
        grafo->insereNo(i);

    grafo->insereAresta(1, 3, 1);
    grafo->insereAresta(1, 4, 4);
    grafo->insereAresta(3, 2, 2);
    grafo->insereAresta(2, 1, 3);
    grafo->insereAresta(5, 4, 3);
    grafo->insereAresta(5, 1, 5);
    grafo->insereAresta(5, 0, 10);

    //cout << "ordem: " << grafo->getOrdem() << endl;
    //cout << "id do primeiro nó: " << grafo->getPrimeiroNo()->getIdNo() << endl; //id do primeiro no
    grafo->printGraph();
    int ordemGrafo = grafo->getOrdem();
    bool visitados[ordemGrafo] = {false};
    float distancia[ordemGrafo] = {__FLT_MAX__};
    cout << "id do nó mais perto do nó 5 : " << grafo->distanciaMinima(visitados, distancia, grafo->getNo(5)) << endl;
    */
// return 0;
// }


#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility> //armazena uma dupla de dados ou objetos (first, second) : https://terminalroot.com.br/2021/08/cpp-pair-e-tuple.html
#include <tuple>  //parecido com o de cima, mas guarda mais de 2 elementos,para acessar:get<x>("variavel") : https://terminalroot.com.br/2021/08/cpp-pair-e-tuple.html
#include <iomanip> //manipula a formatação de saída dos números : https://terminalroot.com.br/2021/05/utilizando-a-biblioteca-iomanip-cpp.html
#include <stdlib.h>
#include <chrono>  //biblioteca de tempo
#include "Grafo.h"
#include "No.h"

using namespace std;

Grafo *leitura(ifstream &input_file, int direcionado, int pesoArestas, int pesoNos) {

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoOrigem;
    int idNoDestino;
    int ordem;

    //Pegando a ordem do grafo
    input_file >> ordem;

    //Criando objeto grafo
    Grafo *graph = new Grafo(ordem, direcionado, pesoArestas, pesoNos);

    //Leitura de arquivo

    if (!graph->getPonderadoArestas() && !graph->getPonderadoNos()) {

        while (input_file >> idNoOrigem >> idNoDestino) {

            graph->insereAresta(idNoOrigem, idNoDestino, 0);

        }

    } else if (graph->getPonderadoArestas() && !graph->getPonderadoNos()) {

        float pesoAresta;

        while (input_file >> idNoOrigem >> idNoDestino >> pesoAresta) {

            graph->insereAresta(idNoOrigem, idNoDestino, pesoAresta);

        }

    } else if (graph->getPonderadoNos() && !graph->getPonderadoArestas()) {

        float pesoNoOrigem, pesoNoDestino;

        while (input_file >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino) {

            graph->insereAresta(idNoOrigem, idNoDestino, 0);
            graph->getNo(idNoOrigem)->setPesoNo(pesoNoOrigem);
            graph->getNo(idNoDestino)->setPesoNo(pesoNoDestino);

        }

    } else if (graph->getPonderadoNos() && graph->getPonderadoArestas()) {

        float pesoNoOrigem, pesoNoDestino, pesoAresta;

        while (input_file >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino) {

            graph->insereAresta(idNoOrigem, idNoDestino, pesoAresta);
            graph->getNo(idNoOrigem)->setPesoNo(pesoNoOrigem);
            graph->getNo(idNoDestino)->setPesoNo(pesoNoDestino);

        }

    }

    return graph;
}

Grafo *leituraInstancia(ifstream &input_file, int direcionado, int pesoArestas, int pesoNos) {

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoOrigem;
    int idNoDestino;
    int ordem;
    int numeroArestas;

    //Pegando a ordem do grafo
    input_file >> ordem;

    //Criando objeto grafo
    Grafo *graph = new Grafo(ordem, direcionado, pesoArestas, pesoNos);

    //Leitura de arquivo
    while (input_file >> idNoOrigem >> idNoDestino) {

        graph->insereAresta(idNoOrigem, idNoDestino, 0);

    }

    return graph;
}

int menu() {

    int selecao;
    cout << endl;
    cout << "   ------  MENU ------" << endl;
    cout << "[1] Fecho transitivo direto de um vertice" << endl;
    cout << "[2] Fecho transitivo indireto de um vertice" << endl;
    cout << "[3] Coeficiente de agrupamento local de um vertice" << endl;
    cout << "[4] Coeficiente de agrupamento medio do grafo" << endl;
    cout << "[5] Caminho Minimo entre dois vertices - Dijkstra " << endl;
    cout << "[6] Caminho Minimo entre dois vertices - Floyd" << endl;
    cout << "[7] Arvore Geradora Minima - Prim" << endl;
    cout << "[8] Arvore Geradora Minima - Kruskal " << endl;
    cout << "[9] Caminhamento em profundidade " << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo *graph, ofstream &output_file) {

    switch (selecao) {

        //Fecho transitivo direto de um vértice ;
        case 1: {
            int id;
            cout << "Digite o ID do vertice para seu fecho transitivo direto: ";
            cin >> id;
            //graph->imprimirFechoTransitivoDireto(output_file, id);
            break;
        }
            //Fecho transitivo indireto de um vértice;
        case 2: {
            int id;
            cout << "Digite o ID do vertice para seu fecho transitivo indireto: ";
            cin >> id;
            //graph->imprimirFechoTransitivoIndireto(output_file, id);
            break;
        }

            //Coeficiente de agrupamento local de um vértice;
        case 3: {
            int id;
            cout << "Digite o ID do vertice: ";
            cin >> id;
            //cout << "Coeficiente do nó " << id << ": " << graph->localClusteringCoefficient(id) << endl;
            break;
        }
            //Coeficiente de agrupamento médio do grafo;
        case 4: {
            cout << "Coeficiente Medio de agrupamento do grafo";
            //cout << " = " << graph->averageClusteringCoefficient() << endl;
            break;
        }
            // Djkstra
            // Caminho Mínimo entre dois vértices - Dijkstra ;
        case 5: {
            int id1, id2;
            cout << "Digite o vértcie de inicio: ";
            cin >> id1;
            cout << "Digite o vértcie final: ";
            cin >> id2;
            //float distancia = graph->dijkstra(id1, id2);
            cout << "A distancia entre " << id1 << " e " << id2 << " é de: " << endl;
            break;
        }


        case 6: {
            int id_one, id_two;
            cout << "Digite o id do vertice de origem: ";
            cin >> id_one;
            cout << "Digite o id do vertice de destino: ";
            cin >> id_two;
            //graph->minimalPathByFloyd(id_one, id_two);
            break;
        }
            //Árvore Geradora Mínima - Prim;
        case 7: {
            cout << "Árvore Geradora Mínima - Prim" << endl;
            //graph->minimalSpanningTreeByPrimAlgorithm(graph->getVerticeInduzido());
            break;
        }
            //Árvore Geradora Mínima - Kruskal;
        case 8: {
            //graph->agmByKruskal(output_file, graph->getVerticeInduzido());
            break;
        }
            //Caminhamento em profundidade
        case 9: {
            // output_file.close();
            int id;
            cout << "Digite o vértice de inicio: ";
            cin >> id;
            //graph->depthFirstSearch(output_file, id);
        }
        default: {
            cout << "Exit!!!" << endl;
        }

    }
}

int mainMenu(ofstream &output_file, Grafo *graph) {

    int selecao = 1;

    while (selecao != 0) {
        // system("clear");
        selecao = menu();

        if (output_file.is_open())
            selecionar(selecao, graph, output_file);

        else
            cout << "Unable to open the output_file" << endl;


        output_file << endl;

    }

    return 0;
}

int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {

        cout
                << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <direcionado> <weighted_edge> <weighted_node> "
                << endl;
        return 1;

    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if (input_file_name.find("v") <= input_file_name.size()) {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    Grafo *graph;
    if (input_file.is_open()) {
        auto start = chrono::steady_clock::now();
        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        auto end = chrono::steady_clock::now();
        cout << "Demorou  "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms para ler o arquivo de entrada." << endl;
        graph->printGraph();
        // graph->printGraphDot(output_file);

    } else
        cout << "Unable to open " << argv[1];

    mainMenu(output_file, graph);

    
    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}
