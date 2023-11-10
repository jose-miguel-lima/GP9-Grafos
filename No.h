#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include "Aresta.h"

using namespace std;

class No{
    private:
        int idNo;
        float pesoNo;
        int grauEntrada;
        int grauSaida;
        bool visitado;
        No* proxNo;
        Aresta* primeiraAresta;
        Aresta* ultimaAresta;

    public:
        No(int idNo, float pesoNo);
        No(int idNo);
        ~No();

        //GETTERS
        int getIdNo();
        float getPesoNo();
        int getGrauEntrada();
        int getGrauSaida();
        bool foiVisitado();
        No* getProxNo();
        Aresta* getPrimeiraAresta();
        Aresta* getUltimaAresta();
        Aresta* getAresta(int idNoDestino);

        //SETTERS
        void setProxNo(No* no);
        void setPesoNo(float peso);
        void setVisita(bool visitadoOuNao);

        //OUTROS METODOS
        bool procuraAresta(int idNoDestino);
        void insereAresta(int idNoDestino, float peso);
        void removeTodasArestas();
        int removeAresta(int id, bool direcionada, No* noDestino);
        void incrementaGrauSaida();
        void decrementaGrauSaida();
        void incrementaGrauEntrada();
        void decrementaGrauEntrada();

        //METODOS AUXILIARES


};

#endif //NO_H_INCLUDED