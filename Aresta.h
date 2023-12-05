#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

#include <iostream>

using namespace std;

class Aresta{
   private:
        int idNoOrigem;
        int idNoDestino;
        double pesoAresta;
        Aresta* proxAresta;

    public:
        Aresta(int idNoOrigem, int idNoDestino);
        Aresta(int idNoDestino);
        ~Aresta();

        int getIdNoOrigem();
        void setIdNoOrigem(int idNoOrigem);

        int getIdNoDestino();
        void setIdNoDestino(int idNoDestino);

        double getPesoAresta();
        void setPesoAresta(double valor);

        Aresta* getProxAresta();
        void setProxAresta(Aresta *proxAresta);

};

#endif //ARESTA_H_INCLUDED