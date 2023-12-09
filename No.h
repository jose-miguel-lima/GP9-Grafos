#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include "Aresta.h"

using namespace std;

class No{
    private:
        int idNo;
        int pesoNo;
        int grauEntrada;
        int grauSaida;
        bool visitado;
        No* proxNo;
        Aresta* primeiraAresta;
        Aresta* ultimaAresta;

        int demanda;
        int x;
        int y;

    public:
        No(int idNo, int x, int y, int demanda);
        No(int idNo, int x, int y);
        No(int idNo, int pesoNo);
        No(int idNo);
        ~No();

        //GETTERS
        int getIdNo();
        int getPesoNo();
        int getGrauEntrada();
        int getGrauSaida();
        bool foiVisitado();
        No* getProxNo();
        Aresta* getPrimeiraAresta();
        Aresta* getUltimaAresta();
        Aresta* getAresta(int idNoDestino);

        int getDemanda();
        int getX();
        int getY();

        //SETTERS
        void setProxNo(No* no);
        void setPesoNo(int peso);
        void setVisita(bool visitadoOuNao);

        void setDemanda(int demanda);
        void setX(int x);
        void setY(int y);

        //OUTROS METODOS
        bool temAresta(int idNoDestino);
        void insereAresta(int idNoDestino, double peso);
        void removeTodasArestas();
        void removeAresta(int idNoDestino, bool direcionada, No* noDestino);
        void incrementaGrauSaida();
        void decrementaGrauSaida();
        void incrementaGrauEntrada();
        void decrementaGrauEntrada();

        //METODOS AUXILIARES

};

#endif //NO_H_INCLUDED