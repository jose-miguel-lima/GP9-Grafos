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

No::~No(){
    Aresta* arestaAtual = this->primeiraAresta;
    while (arestaAtual != nullptr)
    {
        Aresta* auxAresta = arestaAtual->getProxAresta();
        delete arestaAtual;
        arestaAtual = auxAresta;
    }
    
}

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
    }
    
    return NULL;
    
}


//SETTERS
void No::setProxNo(No* no){ //Tratamento de excessão? não pois só consigo fazer no 'insereNo' de Grafo
    this->proxNo = no;
}

void No::setPesoNo(float peso){
    this->pesoNo = peso;
}

void No::setVisita(bool visitadoOuNao){
    this->visitado = visitadoOuNao;
}

//OUTROS METODOS
bool No::procuraAresta(int idNoDestino){
    if(primeiraAresta != NULL){
        Aresta* auxAresta = primeiraAresta;
        int idNoAtual = this->getIdNo();
        while(auxAresta != NULL){
            if( idNoAtual == auxAresta->getIdNoOrigem() && idNoDestino == auxAresta->getIdNoDestino())
                return true;

            auxAresta = auxAresta->getProxAresta();
        }
    }
    
    return false;
    
}

void No::insereAresta(int idNoDestino, float peso){
    Aresta* novaAresta = new Aresta(this->idNo, idNoDestino);
    novaAresta->setPesoAresta(peso);
    
    if(this->primeiraAresta == NULL){
        this->primeiraAresta = novaAresta;
        this->ultimaAresta = novaAresta;
    } else {
        this->ultimaAresta->setProxAresta(novaAresta);
        this->ultimaAresta = novaAresta;   
    }
    
    incrementaGrauSaida();

}

void No::removeTodasArestas(){
    Aresta* auxAresta = primeiraAresta;

    while(auxAresta != NULL){
        primeiraAresta = auxAresta->getProxAresta();
        delete [] auxAresta;
        auxAresta = primeiraAresta;
    }

    this->ultimaAresta = NULL;
}

int removeAresta(int id, bool directed, No* noDestino){
    
    return 1;
}
        
void No::incrementaGrauSaida(){
    this->grauSaida++;
}

void No::decrementaGrauSaida(){
    this->grauSaida--;
}
        
void No::incrementaGrauEntrada(){
    this->grauEntrada++;
}
        
void No::decrementaGrauEntrada(){
    this->grauEntrada--;
}

//METODOS AUXILIARES