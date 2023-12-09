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

//g++ *.cpp -o GP-Grafos    --> compilar
//./GP-Grafos A-n48-k7.vrp testgrafo.txt //INSTANCIA QUE VAMOS USAR


#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <math.h>
#include <utility> //armazena uma dupla de dados ou objetos (first, second) : https://terminalroot.com.br/2021/08/cpp-pair-e-tuple.html
#include <tuple>  //parecido com o de cima, mas guarda mais de 2 elementos,para acessar:get<x>("variavel") : https://terminalroot.com.br/2021/08/cpp-pair-e-tuple.html
#include <iomanip> //manipula a formatação de saída dos números : https://terminalroot.com.br/2021/05/utilizando-a-biblioteca-iomanip-cpp.html
#include <stdlib.h>
#include <chrono>  //biblioteca de tempo
#include "Grafo.h"
#include "No.h"

using namespace std;

Grafo *leitura(ifstream &input_file) {

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoOrigem;
    int idNoDestino;
    int ordem;

    for (int i = 0; i < 3; ++i) {
        string linha;
        getline(input_file, linha);
    }
    //Pegando a ordem do grafo
    string palavra1;
    string palavra2;
    string palavra3;
    int numero;

    // Supondo que a linha tenha o formato "Palavra: 42"
    if (input_file >> palavra1 >> palavra2 >> numero) {     
        ordem = numero;
    }
   

    //Criando objeto grafo
    Grafo *graph = new Grafo(ordem, 0, 1, 1);

    //pula mais 3 linhas
    string linha;
    getline(input_file, linha);
    getline(input_file, linha);
    getline(input_file, linha);
    if (input_file >> palavra1) {     
    }
    //cout << palavra1 << endl;
   


    int id;
    int coordenadaX;
    int coordenadaY;
    for (int i = 0; i < ordem ; i++) {
        if (input_file >> id >> coordenadaX >> coordenadaY) {  
            graph->insereNo(id, coordenadaX, coordenadaY);
        }
    }

 

    string palv ;
    if (input_file >> palv)  {     
    }
    

    int demanda;

    while (input_file >> id >> demanda) {     
            graph->getNo(id)->setPesoNo(demanda);
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
       // auto start = chrono::steady_clock::now();
        graph = leitura(input_file);
       // auto end = chrono::steady_clock::now();
        // cout << "Demorou  "
        //      << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        //      << " ms para ler o arquivo de entrada." << endl;
        
        

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


        // auto end = chrono::steady_clock::now();
        // cout << "Demorou  "
        //      << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        //      << " ms para rodar o algoritmo." << endl;


    } else
        cout << "Unable to open " << argv[1];

    

    
    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}