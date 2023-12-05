#include "Aresta.h"
#include <iostream>

using namespace std;

Aresta::Aresta(int idNoOrigem, int idNoDestino){
    this->idNoOrigem = idNoOrigem;
    this->idNoDestino = idNoDestino;
    this->pesoAresta = 0;
    this->proxAresta = NULL;
}   

//Aresta::Aresta(int idNoDestino){
//    this->idNoOrigem = 0;
//    this->idNoDestino = idNoDestino;
//    this->pesoAresta = 0;
//    this->proxAresta = NULL;
//}

Aresta::~Aresta(){}

int Aresta::getIdNoOrigem(){
    return this->idNoOrigem;
}

void Aresta::setIdNoOrigem(int idNoOrigem){
    this->idNoOrigem = idNoOrigem;
}

int Aresta::getIdNoDestino(){
    return this->idNoDestino;
}

void Aresta::setIdNoDestino(int idNoDestino){
    this->idNoDestino = idNoDestino;
}

double Aresta::getPesoAresta(){
    return this->pesoAresta;
}

void Aresta::setPesoAresta(double valor){
    this->pesoAresta = valor;
}

Aresta* Aresta::getProxAresta(){
    return this->proxAresta;
}

void Aresta::setProxAresta(Aresta *proxAresta){
    this->proxAresta = proxAresta;
}