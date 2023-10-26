#include "No.h"
#include <iostream>

using namespace std;

//Contrutores

No::No(int idNo, float pesoNo){
    this->idNo = idNo;
    this->pesoNo = pesoNo;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->visitado = false;
    this->proxNo = NULL;
    this->primeiraAresta = NULL;
    this->ultimaAresta = NULL;
}

No::No(int idNo){
    this->idNo = idNo;
    this->pesoNo = 1; //peso 1 para não ponderado
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->visitado = false;
    this->proxNo = NULL;
    this->primeiraAresta = NULL;
    this->ultimaAresta = NULL;
}

//Destrutor

No::~No(){}

//GETTERS

int No::getIdNo(){
    return this->idNo;
}

float No::getPesoNo(){
    return this->pesoNo;
}

int No::getGrauEntrada(){
    return this->grauEntrada;
}

int No::getGrauSaida(){
    return this->grauSaida;
}

bool No::foiVisitado(){
    return this->visitado;
}

No* No::getProxNo(){
    return this->proxNo;
}

Aresta* No::getPrimeiraAresta(){
    return this->primeiraAresta;
}

Aresta* No::getUltimaAresta(){
    return this->ultimaAresta;
}

Aresta* No::getAresta(int idNoDestino){
    if(primeiraAresta != NULL){
        Aresta* auxAresta = primeiraAresta;
        int idNoAtual = this->getIdNo();
        while(auxAresta != NULL){
            if( idNoAtual == auxAresta->getIdNoOrigem() && idNoDestino == auxAresta->getIdNoDestino())
                return auxAresta;

            auxAresta = auxAresta->getProxAresta();
        }
    } else {
        return NULL;
    }
}


//SETTERS
