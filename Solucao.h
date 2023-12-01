#ifndef SOLUCAO_H_INCLUDED
#define SOLUCAO_H_INCLUDED

#include <iostream>
#include "Grafo.h"
#include <list>

using namespace std;

class Solucao {
    private:
        
        bool ehViavel;
    
    public:
        Solucao();
        ~Solucao();

        bool getEhViavel();
        void setEhViavel(bool simOuNao);
        bool verificaViabilidade();

};

#endif //SOLUCAO_H_INCLUDED