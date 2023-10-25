#include "Edge.h"

using namespace std;

//CONSTRUTOR E DESTRUTOR


Edge::Edge(int target_id) {
    this->target_id = target_id;
}

// Edge::Edge(int origem, int target_id) {
//     this->target_id = target_id;
//     this->origem = origem;
//     this->weight = 0;
// }

// Edge::Edge(int origem, int target_id, float weight) {
//     this->target_id = target_id;
//     this->origem = origem;
//     this->weight = weight;
// }

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




