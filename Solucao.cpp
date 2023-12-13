#include "Solucao.h"
#include <iostream>

using namespace std;

Solucao::Solucao(int qtdRotas, int qtdNos, int capacidadeRotas){
    this->quantidadeNos = 0;
    this->qtdMaximaNos = qtdNos;
    this->quantidadeDeRotas = qtdRotas;

    for(int i = 0; i < qtdRotas; i++)
        this->rotas.push_back(new Rota(capacidadeRotas));

}

Solucao::Solucao(){
    this->quantidadeNos = 0;
}

Solucao::~Solucao(){}

//GETTERS
Rota* Solucao::getRota(int indiceRota){
    int contador = 1;
    Rota* rotaRetorno = NULL;
    for(auto it = this->rotas.begin(); it != this->rotas.end(); it++){
        if(contador == indiceRota){
            rotaRetorno = *it;        
            break;
        }
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
    if(this->quantidadeNos == this->qtdMaximaNos){
        //se as capacidades não estão negativas, retorna viável == true
        //if(rotas[0]->getCapacidade() >= 0 && rotas[1]->getCapacidade() >= 0 && rotas[2]->getCapacidade() >= 0 && rotas[3]->getCapacidade() >= 0 && rotas[4]->getCapacidade() >= 0 && rotas[5]->getCapacidade() >= 0 && rotas[6]->getCapacidade() >= 0 )
        return true;
    }
    
    return false;
}


void Solucao::PrintaSolucao(){
    for(int i = 1; i <= this->quantidadeDeRotas; i++){
        cout << endl << "Rota " << i << " : ";
        this->getRota(i)->PrintaRota();
    }
    cout << endl;
}

void Solucao::incrementaQtdNos(){
    this->quantidadeNos++;
}