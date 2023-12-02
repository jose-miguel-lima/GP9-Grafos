#include "Rota.h"
#include <iostream>

using namespace std;

Rota::Rota(){
    this->capacidadeAtual = 100;
    this->distanciaPercorrida = 0.0;
}

Rota::~Rota(){}

int Rota::getCapacidade(){
    return this->capacidadeAtual;
}

float Rota::getDistanciaPercorrida(){
    return this->distanciaPercorrida;
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

void Rota::addDistanciaPercorrida(float distancia){
    this->distanciaPercorrida += distancia;
}