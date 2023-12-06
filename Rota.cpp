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

void Rota::addIdNoNaRota(int idNo){//Aceita qualquer um, a verificação de demanda vai ser feita antes de chamar
    this->nosDaRota.push_back(idNo);
}


void Rota::PrintaRota(){
    list<int> r = this->getNosDaRota();
    for(auto it : r)
        cout << it << "  ";
}