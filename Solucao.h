#ifndef SOLUCAO_H_INCLUDED
#define SOLUCAO_H_INCLUDED

#include <iostream>
#include "Rota.h"
#include <list>

using namespace std;

class Solucao {
    private:
        Rota* rotas[7]; // de 0 à 6
        int quantidadeNos;
        double distanciaPercorrida;

    public:
        Solucao();
        ~Solucao();

        Rota* getRota(int indiceRota); // de 0 à 6
        double getDistanciaPercorrida();

        void addIdNoNaRota(int indiceRota, int idNo);
        void addDistanciaPercorrida(double distancia);
        bool verificaViabilidade();

        void PrintaSolucao();
        void incrementaQtdNos();

};

#endif //SOLUCAO_H_INCLUDED