#ifndef SOLUCAO_H_INCLUDED
#define SOLUCAO_H_INCLUDED

#include <iostream>
#include "Rota.h"
#include <list>

using namespace std;

class Solucao {
    private:
        Rota rotas[7]; // de 0 à 6
        int quantidadeNos;
    public:
        Solucao();
        ~Solucao();

        Rota getRota(int indiceRota); // de 0 à 6

        void addIdNoNaRota(int indiceRota, int idNo);
        bool verificaViabilidade();

};

#endif //SOLUCAO_H_INCLUDED