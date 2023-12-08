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


int Grafo::geraNumeroAleatorio(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribuicao(min, max);
    return distribuicao(gen);
}


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

list<int> Grafo::ordenaNosFaltantesPorDistancia(int idNo, list<int> listaNosNaoVisitados){
    list<int> retorno = {};
    No* noBase = this->getNo(idNo);
    int idDoMenor = 10; //qualquer um

    while(!listaNosNaoVisitados.empty()){
        double menorDistancia = __DBL_MAX__;

        for(auto it = listaNosNaoVisitados.begin(); it != listaNosNaoVisitados.end(); it++){
            if(*it != idNo){
                int conteudoIterator = *it;
                double distanciaAux = noBase->getAresta(*it)->getPesoAresta();
                if(distanciaAux < menorDistancia){
                    idDoMenor = *it;
                    menorDistancia = distanciaAux;
                }
            }
        }
        retorno.push_back(idDoMenor);
        listaNosNaoVisitados.remove(idDoMenor);
    }

    return retorno;
}


//vai parar quando não couber alguem em nenhuma rota ou todos os nó forem visitados
bool Grafo::condicaoDeParada(Solucao* solucao){
    if(existeNoNaoVisitado()){
        //Se não cabe em nenhuma rota, return false:
        int demandaPrimeiroNo = getNo(nosNaoVisitados().front())->getPesoNo();
        if(demandaPrimeiroNo > solucao->getRota(0)->getCapacidade())
            if(demandaPrimeiroNo > solucao->getRota(1)->getCapacidade())
                if(demandaPrimeiroNo > solucao->getRota(2)->getCapacidade())
                    if(demandaPrimeiroNo > solucao->getRota(3)->getCapacidade())
                        if(demandaPrimeiroNo > solucao->getRota(4)->getCapacidade())
                            if(demandaPrimeiroNo > solucao->getRota(5)->getCapacidade())
                                if(demandaPrimeiroNo > solucao->getRota(6)->getCapacidade())
                                    return false;
             
    }
    else {  //se todos foram visitados
        return false;
    }
    //não foram todos visitados, mas o primeiro nó cabe em alguma rota
    return true;
}


Solucao* Grafo::guloso1(){
    Solucao* solucao = new Solucao();
    //adiciona o id 1 (depósito) e um no aleatorio em todas as rotas da solucao:
    for(int i = 0; i < 7; i++){
        solucao->getRota(i)->addIdNoNaRota(1);
        int numAleatorio = geraNumeroAleatorio(2, 48);
        //sorteia até achar um não visitado:
        while(getNo(numAleatorio)->foiVisitado()){ 
            numAleatorio = geraNumeroAleatorio(2, 48);
        }
        //adiciona aleatorio na rota i e sua visita:
        solucao->getRota(i)->addIdNoNaRota(numAleatorio);
        
        getNo(numAleatorio)->setVisita(true);
        //aumenta distancia percorrida, diminui capacidade da rota e aumenta quantidade de nós na solucao:
        solucao->addDistanciaPercorrida(this->retornaDistanciaDe(1, numAleatorio));
        solucao->getRota(i)->diminuiCapacidade(getNo(numAleatorio)->getPesoNo());
        solucao->incrementaQtdNos();
    }
    //add que 1 foi visitado
    this->getNo(1)->setVisita(true);
    solucao->incrementaQtdNos();


    //loop de parar ou não de preencher a solucao (PODE SER QUE TENHA QUE MUDAR A CONDIÇÃO)   
    list<int> listaCandidatos = {};
    while(condicaoDeParada(solucao)){
        for(int i = 0; i < 7; i++){
            int idUltimoNoDaRota = solucao->getRota(i)->getNosDaRota().back();
            //cout << "id ultimo nó da rota " << i << " : " << idUltimoNoDaRota << endl;
            listaCandidatos = ordenaNosFaltantesPorDistancia(idUltimoNoDaRota, this->nosNaoVisitados());
            int idPrimeiroCandidato = listaCandidatos.front();
            //se o nó couber na rota, adiciona:
            if(getNo(idPrimeiroCandidato) && (getNo(idPrimeiroCandidato)->getPesoNo() <= solucao->getRota(i)->getCapacidade())){
                //add id na rota, add visitado e aumenta quantidade de nós da solucao:
                solucao->getRota(i)->addIdNoNaRota(idPrimeiroCandidato);
                getNo(idPrimeiroCandidato)->setVisita(true);
                solucao->incrementaQtdNos();

                //add distanciaPercorrida e diminui capacidade da rota:
                double pesoDistancia = getNo(idUltimoNoDaRota)->getAresta(idPrimeiroCandidato)->getPesoAresta();
                solucao->addDistanciaPercorrida(pesoDistancia);
                solucao->getRota(i)->diminuiCapacidade(getNo(idPrimeiroCandidato)->getPesoNo());

            }
            
        }
    }

    //adiciona o 1 como ultimo nó de cada rota e acrescenta a distancia.
    for(int i = 0; i < 7; i++){
        int idUltimoNoDaRota = solucao->getRota(i)->getNosDaRota().back();
        double distanciaAteDeposito = getNo(idUltimoNoDaRota)->getAresta(1)->getPesoAresta();
        solucao->addDistanciaPercorrida(distanciaAteDeposito);
        solucao->getRota(i)->addIdNoNaRota(1);
    }

    cout << endl << "A solucao é viável? (1 == sim  / 0 == não) : " << solucao->verificaViabilidade() << endl;
    cout << "Distancia total percorrida : " << solucao->getDistanciaPercorrida() << endl;
return solucao;
}


int Grafo::indiceCandidatoRandomizado(double alfa, list<int> listaCandidatos){
    int tamanhoDaLista = listaCandidatos.size();
    //Arredonda para o inteiro mais próximo:
    int tamanhoDaListaDiminuido = round(tamanhoDaLista * alfa) + 1;

    // Gera um número aleatório entre 1 e tamanhoDaListaDiminuido
    int indiceCandidato = rand() % tamanhoDaListaDiminuido + 1;
    
    return indiceCandidato;
}


Solucao* Grafo::gulosoRandomizado(double alfa){
    //inicializando semente geradora:
    srand(static_cast<unsigned int>(time(0)));

     Solucao* solucao = new Solucao();
     //adiciona o id 1 (depósito) e um no aleatorio em todas as rotas da solucao:
    for(int i = 0; i < 7; i++){
        solucao->getRota(i)->addIdNoNaRota(1);
        int numAleatorio = geraNumeroAleatorio(2, 48);
        //sorteia até achar um não visitado:
        while(getNo(numAleatorio)->foiVisitado()){ 
            numAleatorio = geraNumeroAleatorio(2, 48);
        }
        //adiciona aleatorio na rota i e sua visita:
        solucao->getRota(i)->addIdNoNaRota(numAleatorio);
        
        getNo(numAleatorio)->setVisita(true);
        //aumenta distancia percorrida, diminui capacidade da rota e aumenta quantidade de nós na solucao:
        solucao->addDistanciaPercorrida(this->retornaDistanciaDe(1, numAleatorio));
        solucao->getRota(i)->diminuiCapacidade(getNo(numAleatorio)->getPesoNo());
        solucao->incrementaQtdNos();
    }
    //add que 1 foi visitado
    this->getNo(1)->setVisita(true);
    solucao->incrementaQtdNos();


    list<int> listaCandidatos = {};
    //loop de parar ou não de preencher a solucao (PODE SER QUE TENHA QUE MUDAR A CONDIÇÃO)   
    while(condicaoDeParada(solucao)){
        for(int i = 0; i < 7; i++){
            int idUltimoNoDaRota = solucao->getRota(i)->getNosDaRota().back();
            //cout << "id ultimo nó da rota " << i << " : " << idUltimoNoDaRota << endl;
            listaCandidatos = ordenaNosFaltantesPorDistancia(idUltimoNoDaRota, this->nosNaoVisitados());
            
            int indiceCandidato = this->indiceCandidatoRandomizado(alfa, listaCandidatos);

            list<int>::iterator iterador = std::next(listaCandidatos.begin(), indiceCandidato - 1 );
            
            int idCandidato = *iterador;
            
            //se o nó couber na rota, adiciona:
            if(getNo(idCandidato) && (getNo(idCandidato)->getPesoNo() <= solucao->getRota(i)->getCapacidade())){
                //add id na rota, add visitado e aumenta quantidade de nós da solucao:
                solucao->getRota(i)->addIdNoNaRota(idCandidato);
                getNo(idCandidato)->setVisita(true);
                solucao->incrementaQtdNos();

                //add distanciaPercorrida e diminui capacidade da rota:
                double pesoDistancia = getNo(idUltimoNoDaRota)->getAresta(idCandidato)->getPesoAresta();
                solucao->addDistanciaPercorrida(pesoDistancia);
                solucao->getRota(i)->diminuiCapacidade(getNo(idCandidato)->getPesoNo());

            }
            
        }
    }

    //adiciona o 1 como ultimo nó de cada rota e acrescenta a distancia.
    for(int i = 0; i < 7; i++){
        int idUltimoNoDaRota = solucao->getRota(i)->getNosDaRota().back();
        double distanciaAteDeposito = getNo(idUltimoNoDaRota)->getAresta(1)->getPesoAresta();
        solucao->addDistanciaPercorrida(distanciaAteDeposito);
        solucao->getRota(i)->addIdNoNaRota(1);
    }

    cout << endl << "A solucao é viável? (1 == sim  / 0 == não) : " << solucao->verificaViabilidade() << endl;
    cout << "Distancia total percorrida : " << solucao->getDistanciaPercorrida() << endl;

    return solucao;
}



