#include "Node.h"

using namespace std;

Node::Node(int id){
    this->id = id;
    this->in_degree = 0;
    this->out_degree = 0;
}

Node::~Node(){}

//GETTERS

Edge* Node::getFirstEdge(){
    return this->first_edge;
}

Edge* Node::getLastEdge(){
    return this->last_edge;
}

int Node::getId(){
    return this->id;
}

int Node::getInDegree(){
    return this->in_degree;
}

int Node::getOutDegree(){
    return this->out_degree;
}

float Node::getWeight(){
    return this->weight;
}

Node* Node::getNextNode(){
    return this->next_node;
}

bool Node::getVisited(){
    return this->visited;
}

//SETTERS

void Node::setNextNode(Node* node){
    this->next_node = node;
}

void Node::setWeight(float weight){
    this->weight = weight;
}

void Node::setVisited(bool visited){
    this->visited = visited;
}

//OUTROS MÉTODOS

void Node::incrementOutDegree(){
    this->out_degree ++;
}

void Node::decrementOutDegree(){
    this->out_degree --;
}

void Node::incrementInDegree(){
    this->in_degree ++;
}

void Node::decrementInDegree(){
    this->in_degree --;
}








