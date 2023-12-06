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
void Grafo::insereNo(int idNo, int x, int y){ //NÃO AUMENTA A ORDEM DO GRAFO DE PROPÓSITO
    
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
    } else {
        cout << "Não foi possivel inserir nó, pois ja existe esse id de nó." << endl;
    }
}

void Grafo::insereArestaEPeso(int idNoOrigem, int idNoDestino, float pesoAresta){
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
        destino->insereAresta( idNoOrigem, pesoAresta);
    }
    
}

void Grafo::insereArestaFase2(int idNoOrigem, int idNoDestino){
    No* origem = getNo(idNoOrigem);
    No* destino = getNo(idNoDestino);

    origem->insereAresta(idNoDestino, this->retornaDistanciaDe(idNoOrigem, idNoDestino));
    if(!this->direcionado){ //Se não é direcionado tem aresta para ambos os lados
        destino->insereAresta( idNoOrigem, this->retornaDistanciaDe(idNoDestino, idNoOrigem));
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

void Grafo::preencheMatrizPesos(){ //começando do no 1, não do 0
    this->matrizPesos = new double*[this->ordem];

    for(int linha = 1; linha <= this->ordem; linha++){
        this->matrizPesos[linha] = new double[this->ordem];
        No* noLinha = getNo(linha);
        for(int coluna = 1; coluna <= this->ordem; coluna++){
            if(linha != coluna)
                this->matrizPesos[linha][coluna] = noLinha->getAresta(coluna)->getPesoAresta();
            else
                this->matrizPesos[linha][coluna] = 0;
        }
    }
}

double Grafo::getPosicaoMatriz(int pos1, int pos2){
    return this->matrizPesos[pos1][pos2];
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


//MÉTODOS fase 2
double Grafo::retornaDistanciaDe(int idNoOrigem, int idNoDestino){
    No* noOrigem = getNo(idNoOrigem);
    No* noDestino = getNo(idNoDestino);

    int x1 = noOrigem->getX();
    int y1 = noOrigem->getY();
    int x2 = noDestino->getX();
    int y2 = noDestino->getY();

    double distancia = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    
    return distancia;
}

list<int> Grafo::ordenaNosFaltantesPorDistancia(int idNo, list<int> listaNosNaoVisitados){
    list<int> retorno = {};
    No* noBase = this->getNo(idNo);
    int idDoMenor = 10; //qualquer um

    while(!listaNosNaoVisitados.empty()){
        double menorDistancia = __DBL_MAX__;

        for(auto it = listaNosNaoVisitados.begin(); it != listaNosNaoVisitados.end(); it++){
            double distanciaAux = noBase->getAresta(*it)->getPesoAresta();
            if(distanciaAux < menorDistancia){
                idDoMenor = *it;
                menorDistancia = distanciaAux;
            }
        }
        retorno.push_back(idDoMenor);
        listaNosNaoVisitados.remove(idDoMenor);
    }

    return retorno;
}

bool Grafo::existeNoNaoVisitado(){
    No* noAux = this->primeiroNo;

    while(noAux != NULL){
        if(!noAux->foiVisitado())
            return true;
        noAux = noAux->getProxNo();
    }

    return false;
}

list<int> Grafo::nosNaoVisitados(){
    list<int> idNos = {};

    No* noAux = this->getPrimeiroNo();
    while(noAux != NULL){
        if(!noAux->foiVisitado()){
            int id = noAux->getIdNo();
            idNos.push_back(id);
        }
        noAux = noAux->getProxNo();
    }

    return idNos;
}

bool Grafo::condicaoDeParada(Solucao* solucao){
    
}


Solucao* Grafo::guloso1(){
    Solucao* solucao = new Solucao();
    //adiciona o id 1 (depósito) e um no aleatorio em todas as rotas da solucao:
    for(int i = 0; i < 7; i++){
        solucao->getRota(i).addIdNoNaRota(1);
        int numAleatorio = geraNumeroAleatorio(2, 48);
        //sorteia até achar um não visitado:
        while(getNo(numAleatorio)->foiVisitado()){ 
            numAleatorio = geraNumeroAleatorio(2, 48);
        }
        //adiciona aleatorio na rota i e sua visita:
        solucao->getRota(i).addIdNoNaRota(numAleatorio);
        getNo(numAleatorio)->setVisita(true);
        //aumenta distancia percorrida e diminui capacidade da rota:
        solucao->addDistanciaPercorrida(this->retornaDistanciaDe(1, numAleatorio));
        solucao->getRota(i).diminuiCapacidade(getNo(numAleatorio)->getPesoNo());
    }
    //add que 1 foi visitado
    this->getNo(1)->setVisita(true);


    list<int> listaCandidatos = {};
    //loop de parar ou não de preencher a solucao (PODE SER QUE TENHA QUE MUDAR A CONDIÇÃO)   
    while(this->existeNoNaoVisitado()){
        for(int i = 0; i < 7; i++){
            int idUltimoNoDaRota = solucao->getRota(i).getNosDaRota().back();
            listaCandidatos = ordenaNosFaltantesPorDistancia(idUltimoNoDaRota, this->nosNaoVisitados());
            int idPrimeiroCandidato = listaCandidatos.front();
            //se o nó couber na rota, adiciona:
            if(getNo(idPrimeiroCandidato)->getPesoNo() <= solucao->getRota(i).getCapacidade()){
                //add id na rota e add visitado:
                solucao->getRota(i).addIdNoNaRota(idPrimeiroCandidato);
                getNo(idPrimeiroCandidato)->setVisita(true);

                //add distanciaPercorrida e diminui capacidade da rota:
                double pesoDistancia = getNo(idUltimoNoDaRota)->getAresta(idPrimeiroCandidato)->getPesoAresta();
                solucao->addDistanciaPercorrida(pesoDistancia);
                solucao->getRota(i).diminuiCapacidade(getNo(idPrimeiroCandidato)->getPesoNo());

            }
            
        }
    }
    
return solucao;
}


int Grafo::geraNumeroAleatorio(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribuicao(min, max);
    return distribuicao(gen);
}



Solucao* Grafo::Guloso2(){
    Solucao* solucao = new Solucao();

    // Define como ponto de partida de todas as rotas o Nó 1
    for(int i = 0; i < 7; i++){
        solucao->getRota(i).addIdNoNaRota(1);
    }

    // Marca o primeiro nó como visitado
    this->getNo(1)->setVisita(true);

    // Cria duas listas para fazer a ordenação e controlar os nós já visitados
    list<int> NosDisponiveis;
    list<int> NosOrdenados;

    // contaRotas para garantir um loop no roteamento da rota 0 a 6;
    int contaRotas = 0;

    // Id do primeiro nó da lista após a ordenação das distâncias
    int IdProxNoRota;

    // Enquanto existir nó que não foi visitado, faça!
    while(!existeNoNaoVisitado()){

        // Refaz a lista de não visitados
        NosDisponiveis = nosNaoVisitados();

        // Reordena a nova lista baseada no id do ultimo nó da rota atual
        NosOrdenados = ordenaNosFaltantesPorDistancia(solucao->getRota(contaRotas).getNosDaRota().back(), NosDisponiveis);

        if(contaRotas == 7){
            // Após rotear a rota 7 volta pra 1
            contaRotas = 0;
        }


        // Recebe o primeiro id da lista ordenada
        IdProxNoRota = NosOrdenados.front();

        // A rota em questão vai receber o id do nó
        solucao->getRota(contaRotas).addIdNoNaRota(IdProxNoRota);

        // Marca o nó como visitado
        this->getNo(IdProxNoRota)->setVisita(true);

        // Diminui a capacidade da rota com base na demanda do nó obtido
        solucao->getRota(contaRotas).diminuiCapacidade(this->getNo(IdProxNoRota)->getDemanda());

        // Remove o nó da lista 
        NosOrdenados.pop_front();
        contaRotas++;
    }

    return solucao;
}