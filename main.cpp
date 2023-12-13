#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <math.h>
#include <utility> //armazena uma dupla de dados ou objetos (first, second) : https://terminalroot.com.br/2021/08/cpp-pair-e-tuple.html
#include <iomanip> //manipula a formatação de saída dos números : https://terminalroot.com.br/2021/05/utilizando-a-biblioteca-iomanip-cpp.html
#include <stdlib.h>
#include <chrono>  //biblioteca de tempo
#include "Grafo.h"

using namespace std;

Grafo *leitura(ifstream &input_file) {

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoOrigem;
    int idNoDestino;
    int ordem;
    string nomeArqv;

    string palavra1;
    string palavra2;
    string palavra3;

    if (input_file >> palavra1 >> palavra2 >> palavra3) {     
        nomeArqv = palavra3;
        cout << "nome arqv: " << nomeArqv << endl;
    }

    string linha;
    getline(input_file, linha);
    getline(input_file, linha);
    getline(input_file, linha);
    

    
    
    int numero;


    if (input_file >> palavra1 >> palavra2 >> numero) {     
        ordem = numero;
        cout << "ordem: " << numero << endl;
    }
   
   
    //Criando objeto grafo
    Grafo *graph = new Grafo(ordem, 0, 1, 1);
    graph->setNomeArqv(nomeArqv);
    cout << "-----------" << endl;
    //pula mais 3 linhas
    if(nomeArqv == "Golden_1" || nomeArqv == "Golden_17") {
        getline(input_file, linha);
    }
    getline(input_file, linha);
    getline(input_file, linha);
    getline(input_file, linha);
    if (input_file >> palavra1) {     
    }

    int id;
    double coordenadaX;
    double coordenadaY;
    for (int i = 0; i < ordem ; i++) {
        if (input_file >> id >> coordenadaX >> coordenadaY) {  
            graph->insereNo(id, coordenadaX, coordenadaY);
            cout << "id: " << id << " coordenadaX: " << coordenadaX << " coordenadaY: " << coordenadaY << endl;
        }
    }

    string palv ;
    if (input_file >> palv)  {     
    }
    

    int demanda;

    while (input_file >> id >> demanda) {     
            graph->getNo(id)->setPesoNo(demanda);
            cout << "id: " << id << " demanda: " << demanda << endl;
    }

    return graph;
}

int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 3) {

        cout
                << "ERROR: Expecting: ./<program_name> <input_file> <output_file>"
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

        graph = leitura(input_file);
   
        //preencheAresta
        for(int i = 1; i < graph->getOrdem() + 1; i++) {
            for(int j = 1; j < graph->getOrdem() + 1; j++) {
                if(!graph->existeAresta(i, j) && i != j) {
                    graph->insereArestaFase2(i, j);
                }
            }
        }
        ///////////// PODE CHAMAR OS MÉTODOS AQUI DE GRAFO
        auto start = chrono::steady_clock::now();

        //TESTAR QUALQUER INSTANCIA
        //capacidade
        cout << "nomearqv : " << graph->getNomeArqv() << endl;
        if(graph->getNomeArqv() == "A-n34-k5") {
            graph->setQuantidadeRotas(5);
        }
         if(graph->getNomeArqv() == "A-n48-k7") {
            graph->setQuantidadeRotas(7);
        }
         if(graph->getNomeArqv() == "B-n34-k5") {
            graph->setQuantidadeRotas(5);
        }
         if(graph->getNomeArqv() == "B-n50-k8") {
            graph->setQuantidadeRotas(8);
        }
         if(graph->getNomeArqv() == "Golden_1") {
            graph->setQuantidadeRotas(9);
        }
         if(graph->getNomeArqv() == "Golden_17") {
            graph->setQuantidadeRotas(22);
        }
         if(graph->getNomeArqv() == "M-n101-k10") {
            graph->setQuantidadeRotas(10);
        }
         if(graph->getNomeArqv() == "M-n151-k12") {
            graph->setQuantidadeRotas(12);
        }
         if(graph->getNomeArqv() == "X-n101-k25") {
            graph->setQuantidadeRotas(25);
        }
         if(graph->getNomeArqv() == "X-n280-k17") {
            graph->setQuantidadeRotas(17);
        }

        cout << "Qunatidade de rotas é : " << graph->getQtdRotas() << endl;
        int escolha = 1;
        int qtdExecucoes;
        double alfa;

        cout << endl << "============== BEM VINDO AO TRABALHO DE GRAFOS DO GRUPO 9 ==============" << endl << endl;

        cout << "FASE 2 " << endl;
        cout << "                            MENU                            " << endl;
        cout << "Escolha um algoritmo para resolver o problema de roteamento de veículo: " << endl;
        cout << "(1) Guloso " << endl;
        cout << "(2) Guloso Randomizado " << endl << endl;
        cout << "Escolha : ";
        cin >> escolha;
            

        switch (escolha)
        {
        case 1:
                 graph->guloso1()->PrintaSolucao();   
            break;
        case 2:
            cout << "Qual alfa gostaria de passar para o Guloso Randomizado? [0, 1] :";
            cin >> alfa;
                graph->gulosoRandomizado(alfa)->PrintaSolucao();
            break;
        default:
            cout << "Desculpe, essa opção não existe ! " << endl;
            break;
        }


        auto end = chrono::steady_clock::now();
        cout << "Demorou  "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms para rodar o algoritmo." << endl;


    } else
        cout << "Unable to open " << argv[1];

    

    
    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}