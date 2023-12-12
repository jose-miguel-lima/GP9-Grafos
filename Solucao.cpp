#include "Solucao.h"
#include <iostream>

using namespace std;

Solucao::Solucao(int qtdRotas){
    this->quantidadeNos = 0;
    this->quantidadeDeRotas = qtdRotas;
    this->rotas(qtdRotas); //opção de add "(qtdRotas, NULL);"
    for (int i = 0; i < qtdRotas; i++) {
        rotas[i] = new Rota();
    }
}

Solucao::~Solucao(){}

//GETTERS
Rota* Solucao::getRota(int indiceRota){
    int contador = 0;
    for(auto it = this->rotas.begin(); it != this->rotas.end(); it++){
        Rota* rotaRetorno = *it;        
        if(contador == indiceRota)
            break;
        contador++;
    }

    return rotaRetorno;
}

double Solucao::getDistanciaPercorrida(){
    return this->distanciaPercorrida;
}

int Solucao::getQtdRotas(){
    return this->quantidadeDeRotas;
}

//SETTERS

void Solucao::addIdNoNaRota(int indiceRota, int idNo){
//aceita tudo, deve-se verificar antes de chamar e funcao e atualizar a capacidade da rota na Grafo.cpp
    this->getRota(indiceRota)->addIdNoNaRota(idNo);
    this->quantidadeNos++;
}

void Solucao::addDistanciaPercorrida(double distancia){
    this->distanciaPercorrida += distancia;
}

//MUDAR MUDAR MUDAR
bool Solucao::verificaViabilidade(){  
    if(this->quantidadeNos == 48){
        //se as capacidades não estão negativas, retorna viável == true
        if(rotas[0]->getCapacidade() >= 0 && rotas[1]->getCapacidade() >= 0 && rotas[2]->getCapacidade() >= 0 && rotas[3]->getCapacidade() >= 0 && rotas[4]->getCapacidade() >= 0 && rotas[5]->getCapacidade() >= 0 && rotas[6]->getCapacidade() >= 0 )
            return true;
    }
    
    return false;
}


void Solucao::PrintaSolucao(){
    for(int i = 0; i < this->quantidadeDeRotas; i++){
        cout << endl << "Rota " << i+1 << " : ";
        this->getRota(i)->PrintaRota();
    }
    cout << endl;
}

void Solucao::incrementaQtdNos(){
    this->quantidadeNos++;
}