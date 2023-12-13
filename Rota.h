#ifndef ROTA_H_INCLUDED
#define ROTA_H_INCLUDED

#include <iostream>
#include <list>

using namespace std;

class Rota {
    private:
        list<int> nosDaRota;
        int capacidadeAtual;

    public:
        Rota(int capacidade);
        ~Rota();

        int getCapacidade();
        
        list<int> getNosDaRota();

        void diminuiCapacidade(int valor);
        void addIdNoNaRota(int idNo);

        void PrintaRota();
};

#endif //ROTA_H_INCLUDED