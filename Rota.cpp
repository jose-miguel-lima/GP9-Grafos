#include "Rota.h"
#include <iostream>

using namespace std;

Rota::Rota(){
    this->capacidadeAtual = 100;
}

Rota::~Rota(){}

int Rota::getCapacidade(){
    return this->capacidadeAtual;
}

list<int> Rota::getNosDaRota(){
    return this->nosDaRota;
}

void Rota::diminuiCapacidade(int valor){
    this->capacidadeAtual -= valor;
}

void Rota::addNoNaRota(int idNo){
    this->nosDaRota.push_back(idNo);
}