#include "Grafo.h"
#include <iostream>

using namespace std;

Grafo::Grafo(int ordem, bool direcionado, bool pesoArestas, bool pesoNos){
    this->ordem = ordem;
    this->direcionado = direcionado;
    this->ponderadoArestas = pesoArestas;
    this->ponderadoNos = pesoNos;
    this->numArestas = 0;
    this->primeiroNo = NULL;
    this->ultimoNo = NULL;
}

Grafo::~Grafo(){
    No *noAtual = this->primeiroNo;
    while(noAtual != nullptr){
        No *auxNo = noAtual->getProxNo();
        delete noAtual;
        noAtual = auxNo;
    }
    this->ordem = 0;
    this->numArestas = 0;
    this->primeiroNo = NULL;
    this->ultimoNo = NULL;
}

//GETTERS
int Grafo::getOrdem(){
    return this->ordem;
}

int Grafo::getNumArestas(){
    return this->numArestas;
}
        
bool Grafo::getDirecionado(){
    return this->direcionado;
}
        
bool Grafo::getPonderadoArestas(){
    return ponderadoArestas;
}
        
bool Grafo::getPonderadoNos(){
    return this->ponderadoNos;
}
        
No* Grafo::getPrimeiroNo(){
    return this->primeiroNo;
}
        
No* Grafo::getUltimoNo(){
    return this->ultimoNo;
}


//OUTROS MÉTODOS
void Grafo::insereNo(int idNo, int x, int y){ //SERÁ QUE NÃO PRECISA DO PESO COMO PARÂMETRO ???
    
    if(!existeNo(idNo)){
        if(primeiroNo != NULL){
            No* novoNo = new No(idNo, x, y);
            this->ultimoNo->setProxNo(novoNo);
            this->ultimoNo = novoNo;
        } else { //primeiroNo = NULL
            No* novoNo = new No(idNo, x, y);
            this->primeiroNo = novoNo;
            this->ultimoNo = novoNo;
        }
        this->ordem++;
    } else {
        cout << "Não foi possivel inserir nó, pois ja existe esse id de nó." << endl;
    }
}

void Grafo::insereNoPonderado(int idNo, float pesoNo){

    if(!existeNo(idNo)){
        if(primeiroNo != NULL){
        No* novoNo = new No(idNo, pesoNo);
            this->ultimoNo->setProxNo(novoNo);
            this->ultimoNo = novoNo;
        } else { //primeiroNo = NULL
            No* novoNo = new No(idNo, pesoNo);
            this->primeiroNo = novoNo;
            this->ultimoNo = novoNo;
        }
        this->ordem++;
    } else {
        cout << "Não foi possivel inserir nó, pois ja existe esse id de nó." << endl;
    }
}

void Grafo::insereAresta(int idNoOrigem, int idNoDestino, float pesoAresta){
    if(!existeNo(idNoOrigem)){
        //agora insere no tem x e y ai estava dando erro e coloquei esse 0 e 0 , na segunda parte acredito que não vamos criar nos assim
        this->insereNo(idNoOrigem, 0, 0);
    }
    if(!existeNo(idNoDestino)){
        this->insereNo(idNoDestino,0 ,0);
    }
    
    No* origem = getNo(idNoOrigem);
    No* destino = getNo(idNoDestino);

    origem->insereAresta(idNoDestino, pesoAresta);
    if(!this->direcionado){ //Se não é direcionado tem aresta para ambos os lados
        destino->insereAresta(idNoOrigem, pesoAresta);
    }
    
}

void Grafo::removeNo(int idNo){
    if(existeNo(idNo)){
        //ADD REMOVER TODAS ARESTAS LIGADAS AO NÓ

        No* noAnterior = this->primeiroNo;
        if(this->primeiroNo->getIdNo() == idNo){ //se for remover o primeiro
            this->primeiroNo = this->primeiroNo->getProxNo();
            delete noAnterior;
        } else { //não é o primeiro a ser removido
            No* noDelete = noAnterior->getProxNo();
            while(noDelete->getIdNo() != idNo){
                noDelete = noDelete->getProxNo();
                noAnterior = noAnterior->getProxNo();
            }

            noAnterior->setProxNo(noDelete->getProxNo());
            delete noDelete;
        }

        this->ordem--;
    }
}

bool Grafo::existeNo(int idNo){
    if(this->primeiroNo != NULL){
        No* noAux = this->primeiroNo;
        while(noAux != NULL){
            if(noAux->getIdNo() == idNo){
                return true;
            }
            noAux = noAux->getProxNo();
        }
    }
    
    return false;
}

No* Grafo::getNo(int idNo){
    No* noAux = this->primeiroNo;
    while(noAux != NULL){
        if(noAux->getIdNo() == idNo)
            return noAux;

        noAux = noAux->getProxNo();
    }
    return NULL;
}

bool Grafo::existeAresta(int idNoOrigem, int idNoDestino){
    if(existeNo(idNoOrigem) && existeNo(idNoDestino)){
        No* noAux = getNo(idNoOrigem);
        return noAux->temAresta(idNoDestino); //retorna bool
    } else {
        return false;
    }
}

int Grafo::indiceDistanciaMinima(bool visitados[], float distancia[]){
    float menor = __FLT_MAX__;
    int indiceDoMenor = -1;
    for(int i = 0; i < this->ordem; i++){
        if(visitados[i] == false && distancia[i] < menor){
            menor = distancia[i];
            indiceDoMenor = i;
        }
    }
    for(int i = 0; i < this->ordem; i++){
        if(indiceDoMenor == -1 && visitados[i] == false)
            indiceDoMenor = i;
    }
    
    return indiceDoMenor; //Se retornar -1 é pq todos ja foram visitados;
}

int Grafo::distanciaMinimaDijkstra(bool visitados[], float distancia[], No* noBase){
    int indiceDaVez = noBase->getIdNo();
    for(int i = 0; i < this->ordem; i++){ //inicializa os vetores
        if(noBase->temAresta(i)){
            distancia[i] = noBase->getAresta(i)->getPesoAresta();
        } else {
            distancia[i] = __FLT_MAX__;
        }

        if(i == indiceDaVez){
            visitados[i] = true;
            distancia[i] = 0;
        }
    }
    
    for(int interacao = 1; interacao < this->ordem; interacao++){
        indiceDaVez = indiceDistanciaMinima(visitados, distancia);
        if(indiceDaVez == -1) //todos ja foram visitados
            break;
        for(int correVetor = 0; correVetor < this->ordem; correVetor++){
            visitados[indiceDaVez] = true;
            //Se a soma das arestas do noBase até o nó possivel de mudança for menor que a atual, muda 
            if(visitados[correVetor] == false && existeAresta(indiceDaVez, correVetor) && distancia[indiceDaVez] + pesoAresta(indiceDaVez, correVetor) < distancia[correVetor]){
                distancia[correVetor] = distancia[indiceDaVez] + pesoAresta(indiceDaVez, correVetor);
            }
        }
    }

    int menor = 0;
    for(int i = 1; i < this->ordem; i++){
        if(visitados[i] == false)
            cout << "Existe um erro no código, Pois todos deveriam ser visitados!" << endl;
        
        if( i != noBase->getIdNo() && distancia[i] < distancia[menor])
            menor = i;
    }

    return menor;
}


//MÉTODOS ADICIONADOS POR NÓS
void Grafo::incrementaGrauEntradaPorId(int idNo){
    No* noAux = this->primeiroNo;
    while(noAux != NULL){
        if(noAux->getIdNo() == idNo)
            noAux->incrementaGrauEntrada();
        noAux = noAux->getProxNo();
    }
}

float Grafo::pesoAresta(int idNoOrigem, int idNoDestino){
    No* origem = getNo(idNoOrigem);
    return origem->getAresta(idNoDestino)->getPesoAresta();
}

void Grafo::preencheMatrizPesos(){
    this->matrizPesos = new float*[this->ordem];

    for(int linha = 0; linha < this->ordem; linha++){
        this->matrizPesos[linha] = new float[this->ordem];
        No* noLinha = getNo(linha);
        for(int coluna = 0; coluna < this->ordem; coluna++){
            if(linha != coluna)
                this->matrizPesos[linha][coluna] = noLinha->getAresta(coluna)->getPesoAresta();
            else
                this->matrizPesos[linha][coluna] = 0;
        }
    }
}

void Grafo::desalocaMatriz(){
    for(int i = 0; i < this->ordem; i++){
        delete [] this->matrizPesos[i];
    }
    delete [] this->matrizPesos;
}

//metodos auxiliares
void Grafo::printGraph(){
    if(this->getPrimeiroNo() != NULL){
        No* noAux = this->primeiroNo;
        while (noAux != NULL){
            cout << noAux->getIdNo();
            Aresta* auxAresta = noAux->getPrimeiraAresta();
            while (auxAresta != NULL){
                cout << "-->" << auxAresta->getIdNoDestino();
                auxAresta = auxAresta->getProxAresta();
            }
            cout << endl;
            noAux = noAux->getProxNo();
        }
    }
}