#include "Solucao.h"
#include <iostream>

using namespace std;

Solucao::Solucao(){
    this->quantidadeNos = 0;
    this->rotas[0] = new Rota();
    this->rotas[1] = new Rota();
    this->rotas[2] = new Rota();
    this->rotas[3] = new Rota();
    this->rotas[4] = new Rota();
    this->rotas[5] = new Rota();
    this->rotas[6] = new Rota();
}

Solucao::~Solucao(){}

//GETTERS
Rota* Solucao::getRota(int indiceRota){
    return this->rotas[indiceRota];
}

double Solucao::getDistanciaPercorrida(){
    return this->distanciaPercorrida;
}

//SETTERS

void Solucao::addIdNoNaRota(int indiceRota, int idNo){
//aceita tudo, deve-se verificar antes de chamar e funcao e atualizar a capacidade da rota na Grafo.cpp
    this->rotas[indiceRota]->addIdNoNaRota(idNo);
    this->quantidadeNos++;
}

void Solucao::addDistanciaPercorrida(double distancia){
    this->distanciaPercorrida += distancia;
}

bool Solucao::verificaViabilidade(){
    if(this->quantidadeNos == 48){
        //se as capacidades não estão negativas, retorna viável == true
        if(rotas[0]->getCapacidade() >= 0 && rotas[1]->getCapacidade() >= 0 && rotas[2]->getCapacidade() >= 0 && rotas[3]->getCapacidade() >= 0 && rotas[4]->getCapacidade() >= 0 && rotas[5]->getCapacidade() >= 0 && rotas[6]->getCapacidade() >= 0 )
            return true;
    }
    
    return false;
}


void Solucao::PrintaSolucao(){
    for(int i = 0; i < 7; i++){
        cout << endl << "Rota " << i+1 << " : ";
        this->getRota(i)->PrintaRota();
    }
    cout << endl;
}

void Solucao::incrementaQtdNos(){
    this->quantidadeNos++;
}