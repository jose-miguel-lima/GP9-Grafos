#include "Grafo.h"
#include <iostream>

using namespace std;

Grafo::Grafo(int ordem, bool direcionado, bool pesoArestas, bool pesoNos){
    this->ordem = ordem;
    this->direcionado = direcionado;
    this->ponderadoArestas = pesoArestas;
    this->ponderadoNos = pesoNos;
    this->numArestas = 0;
    this->primeiroNo = NULL;
    this->ultimoNo = NULL;
}

Grafo::~Grafo(){
    No *noAtual = this->primeiroNo;
    while(noAtual != nullptr){
        No *auxNo = noAtual->getProxNo();
        delete noAtual;
        noAtual = auxNo;
    }
    this->ordem = 0;
    this->numArestas = 0;
    this->primeiroNo = NULL;
    this->ultimoNo = NULL;
}

//GETTERS
int Grafo::getOrdem(){
    return this->ordem;
}

int Grafo::getNumArestas(){ //só retorna o numero de arestas
    return this->numArestas;
}
        
bool Grafo::getDirecionado(){
    return this->direcionado;
}
        
bool Grafo::getPonderadoArestas(){
    return ponderadoArestas;
}
        
bool Grafo::getPonderadoNos(){
    return this->ponderadoNos;
}
        
No* Grafo::getPrimeiroNo(){
    return this->primeiroNo;
}
        
No* Grafo::getUltimoNo(){
    return this->ultimoNo;
}


//OUTROS MÉTODOS
void Grafo::insereNo(int idNo){ //SERÁ QUE NÃO PRECISA DO PESO COMO PARÂMETRO ???
    
    if(!existeNo(idNo)){

        if(primeiroNo != NULL){
            No* novoNo = new No(idNo);
            this->ultimoNo->setProxNo(novoNo);
            this->ultimoNo = novoNo;
        } else { //primeiroNo = NULL
            No* novoNo = new No(idNo);
            this->primeiroNo = novoNo;
            this->ultimoNo = novoNo;
        }
        this->ordem++;
    } else {
        cout << "Não foi possivel inserir nó, pois ja existe esse id de nó." << endl;
    }
}

void Grafo::insereAresta(int idNoOrigem, int idNoDestino, float pesoAresta){
    No* noAux = this->primeiroNo;
    while(noAux != NULL){
        if(noAux->getIdNo() == idNoOrigem){
            noAux->insereAresta(idNoDestino, pesoAresta);
            incrementaGrauEntradaPorId(idNoDestino); //grau de entrada++ no noDestino
            break;
        }
        noAux = noAux->getProxNo();
    }
}

void Grafo::removeNo(int idNo){
    if(existeNo(idNo)){
        No* noAnterior = this->primeiroNo;
        if(this->primeiroNo->getIdNo() == idNo){
            this->primeiroNo = this->primeiroNo->getProxNo();
            delete noAnterior;
        } else {
            No* noDelete = noAnterior->getProxNo();
            while(noDelete->getIdNo() != idNo){
                noDelete = noDelete->getProxNo();
                noAnterior = noAnterior->getProxNo();
            }

            noAnterior->setProxNo(noDelete->getProxNo());
            delete noDelete;
        }

        this->ordem--;
    }
}

bool Grafo::existeNo(int idNo){
    if(this->primeiroNo != NULL){
        No* noAux = this->primeiroNo;
        while(noAux != NULL){
            if(noAux->getIdNo() == idNo){
                return true;
            }
            noAux = noAux->getProxNo();
        }
    }
    
    return false;
}

No* Grafo::getNo(int idNo){
    No* noAux = this->primeiroNo;
    while(noAux != NULL){
        if(noAux->getIdNo() == idNo)
            return noAux;

        noAux = noAux->getProxNo();
    }
    return NULL;
}

bool Grafo::existeAresta(int idNoOrigem, int idNoDestino){
    if(existeNo(idNoOrigem) && existeNo(idNoDestino)){
        No* noAux = getNo(idNoOrigem);
        return noAux->procuraAresta(idNoDestino); //retorna bool
    } else {
        return false;
    }
}

int Grafo::distanciaMinima(bool visitados[], float distancia[]){ //o vetor de distancia float ??

} 


//MÉTODOS ADICIONAIS
void Grafo::incrementaGrauEntradaPorId(int idNo){
    No* noAux = this->primeiroNo;
    while(noAux != NULL){
        if(noAux->getIdNo() == idNo)
            noAux->incrementaGrauEntrada();
        noAux = noAux->getProxNo();
    }
}