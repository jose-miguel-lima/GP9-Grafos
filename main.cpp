#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

using namespace std;



int main() {

    cout << "OLÀ" << endl;

    Node *no = new Node(2);
    cout << "o id é " << no->getId() << endl;

    Edge *aresta = new Edge(4);

    cout << "o id alvo é " << aresta->getTargetId() << endl;





    /// TESTE ZONA 
    

    ///
    // //nos digitasdos sao stings? se sim pega vetor 0 e vetor 1
    // //Grafo* g = new Grafo();
    // cout << "Digite o número de nós do grafo." << endl;
    // int nos;
    // cin >> nos;


    // int numMaxArestas = (nos * (nos - 1)) / 2;
   
    // int *vetorRelacoes = new int[numMaxArestas];

    // int i = 0;
    // int valor = 1;
    // cout << "Digite as relações e para continuar o programa digite 0: " << endl;
    // while (valor != 0)
    // {
    //     cin >> valor;
    //     vetorRelacoes[i] = valor;
    //     i++;
    // }
    // //retirar o 0 da contagem
    // i = i - 1;

    // int qtdArestas = i;
    // for (int j = 0; j < qtdArestas; j++)
    // {
    //     cout << vetorRelacoes[j] << " - ";
    //     j++;
    //     cout << vetorRelacoes[j] << endl;
    // }

    // bool ehDirecionado;
    // cout << "Seu grafo eh direcionado? (1) Direcionado ou (0) Nao Direcionado: ";
    // cin >> ehDirecionado;
    // cout << "Eh direcionado: " << ehDirecionado << endl;
    // //g->setDirecionado(ehDirecionado);

    // bool ehPonderado;
    // cout << "Seu grafo eh Ponderado? (1) Ponderado ou (0) Nao Ponderado: ";
    // cin >> ehPonderado;
    // cout << "Eh ponderado: " << ehPonderado << endl;
    // //g->setPonderado(ehPonderado);

    // // Criando grafo a partir de uma lista de adjacencia
    // //cout << "Aguarde enquanto o grafo esta sendo criado..." << endl;
    // //criaGrafoListaAdj(g, entrada);


    // delete[] vetorRelacoes;
    // return 0;

    return 0;
}