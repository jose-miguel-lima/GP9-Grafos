#ifndef SOLUCAO_H_INCLUDED
#define SOLUCAO_H_INCLUDED

#include <iostream>
#include "Rota.h"
#include <list>

using namespace std;

class Solucao {
    private:
        list<Rota*> rotas; 
        int quantidadeNos;
        double distanciaPercorrida;
        int quantidadeDeRotas;

    public:
        Solucao(int qtdRotas);
        ~Solucao();

        Rota* getRota(int indiceRota); 
        double getDistanciaPercorrida();
        int getQtdRotas();

        void addIdNoNaRota(int indiceRota, int idNo);
        void addDistanciaPercorrida(double distancia);
        bool verificaViabilidade();

        void PrintaSolucao();
        void incrementaQtdNos();

};

#endif //SOLUCAO_H_INCLUDED