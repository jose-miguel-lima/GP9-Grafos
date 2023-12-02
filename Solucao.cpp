#include "Solucao.h"
#include <iostream>

using namespace std;

Solucao::Solucao(){
    this->quantidadeNos = 0;
}

Solucao::~Solucao(){}

//GETTERS
Rota Solucao::getRota(int indiceRota){
    return this->rotas[indiceRota];
}

//SETTERS

void Solucao::addIdNoNaRota(int indiceRota, int idNo){
//aceita tudo, deve-se verificar antes de chamar e funcao e atualizar a capacidade da rota na Grafo.cpp
    this->rotas[indiceRota].addIdNoNaRota(idNo);
    this->quantidadeNos++;
}

bool Solucao::verificaViabilidade(){
    if(this->quantidadeNos == 61){ //(47 + 14)pois são 47 nós sem o deposito e tem 7 rotas, em cada rota tem 2 depositos (7 * 2 == 14)
        if(rotas[0].getCapacidade() >= 0 && rotas[1].getCapacidade() >= 0 && rotas[2].getCapacidade() >= 0 && rotas[3].getCapacidade() >= 0 && rotas[4].getCapacidade() >= 0 && rotas[5].getCapacidade() >= 0 && rotas[6].getCapacidade() >= 0 )
            return true;
    }
    else 
        return false;
}