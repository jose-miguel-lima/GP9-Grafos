#ifndef ROTA_H_INCLUDED
#define ROTA_H_INCLUDED

#include <iostream>
#include "Grafo.h"
#include <list>

using namespace std;

class Rota {
    private:
        list<int> nosDaRota;
        int capacidadeAtual;

    public:
        Rota();
        ~Rota();

        int getCapacidade();
        list<int> getNosDaRota();

        void diminuiCapacidade(int valor);
        void addNoNaRota(int idNo);
};

#endif //ROTA_H_INCLUDED