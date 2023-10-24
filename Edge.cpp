#include "Edge.h"

using namespace std;

//CONSTRUTOR E DESTRUTOR

//esse construtor acredito que será chamado em nó, então vai ser conmstruida uma aresta por meio de um método de nó, então esse construtor será acrescentado informações
Edge::Edge(int target_id) {
    this->target_id = target_id;
}

Edge::~Edge(){}

//GETTERS

int Edge::getTargetId(){
    return this->target_id;
}

int Edge::getOrigem(){
    return this->origem;
}

Edge* Edge::getNextEdge(){
    return this->next_edge;
}

float Edge::getWeight(){
    return this->weight;
}

//SETTERS

void Edge::setNextEdge(Edge *edge){
    this->next_edge = edge;
}

void Edge::setWeight(float weight){
    this->weight = weight;
}

void Edge::setOrigem(int origem){
    this->origem = origem;
}




