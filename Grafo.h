#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "No.h"
#include "Solucao.h"
#include <fstream>
#include <stack>
#include <list>

using namespace std;


class Grafo {
    private:
        int ordem;
        int numArestas;
        bool direcionado;
        bool ponderadoArestas;
        bool ponderadoNos;
        No *primeiroNo;
        No *ultimoNo;
        float** matrizPesos;

    public:
        Grafo(int ordem, bool direcionado, bool pesoArestas, bool pesoNos);
        ~Grafo();

        //GETTERS:
        int getOrdem();

        int getNumArestas();
        
        bool getDirecionado();
        
        bool getPonderadoArestas();
        
        bool getPonderadoNos();
        
        No* getPrimeiroNo();
        
        No* getUltimoNo();


        //OUTROS MÉTODOS:
        void insereNo(int idNo, int x, int y);
        
        void insereNoPonderado(int idNo, float pesoNo);

        void insereAresta(int idNoOrigem, int idNoDestino, float pesoAresta);//VERIFICAR DIREÇÃO

        void removeNo(int idNo); //remover arestas do nó

        bool existeNo(int idNo);

        No* getNo(int idNo);

        bool existeAresta(int idNoOrigem, int idNoDestino);

        int indiceDistanciaMinima(bool visitados[], float distancia[]);
        //retorna o id do nó mais perto do noBase
        int distanciaMinimaDijkstra(bool visitados[], float distancia[], No* noBase);

        //METODOS ADICIONADOS POR NÓS
        //void incrementaNumArestas();
        //void decrementaNumArestas();
        //void incrementaOrdem();
        //void decrementaOrdem();
        void incrementaGrauEntradaPorId(int idNo);
        float pesoAresta(int idNoOrigem, int idNodestino);
        void preencheMatrizPesos();
        void desalocaMatriz();

        //auxiliar methods
        void printGraph();
        
        //METODOS FASE 2: 
        public:
            
};


/*
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <map>

using namespace std;
struct Aresta_aux {
    int origem;
    int destino;
    int peso;
};

typedef struct {
    int id_origem;
    Node *k;
    Edge *e;
} EdgeLinkedNode;
*/
/*
class Graph {

    //Atributes
private:
    int order;
    int number_edges;
    bool directed;
    bool weighted_edge;
    bool weighted_node;
    Node *first_node;
    Node *last_node;

public:
    //Constructor
    Graph(int order, bool directed, bool weighted_edge, bool weighted_node);

    //Destructor
    ~Graph();

    //Getters
    int getOrder();

    int getNumberEdges();

    bool getDirected();

    bool getWeightedEdge();

    bool getWeightedNode();

    Node *getFirstNode();

    Node *getLastNode();

    //Other methods
    void insertNode(int id);

    void insertEdge(int id, int target_id, float weight);

    void removeNode(int id);

    bool searchNode(int id);

    Node *getNode(int id);

    bool searchEdge(int id, int target_id);

    int minimalDistance(bool visitados[], float dist[]);

    //methods phase1
    void topologicalSorting();

    void breadthFirstSearch(ofstream &output_file);

    void depthFirstSearch(ofstream &output_file, int id);

    list<int> getFechoTransitivoDireto(list<int> &fechoDireto, int *id); //fecho transitivo direto
    list<int> getFechoTransitivoIndireto(list<int> &fechoIndireto, int *id);//fecho transitivo indireto
    void imprimirFechoTransitivoDireto(ofstream &output_file, int id);//fecho transitivo direto
    void imprimirFechoTransitivoIndireto(ofstream &output_file, int id);//fecho transitivo indireto
    void agmByKruskal(ofstream &outputFile, Graph *grafo);

    void imprimirAgmByKruskal(ofstream &outputfile, int ordem, int numero_arestas, Aresta_aux arestas_finais[]);

    Graph *getVerticeInduzido(); //obter subgrafo induzido

    Graph *agmPrim();

    float floydMarshall(int idSource, int idTarget);

    float dijkstra(int idSource, int idTarget);

    float localClusteringCoefficient(int idNode);

    float averageClusteringCoefficient();

    void auxDijkstra(float *dist, int *aPercorrer, int *noAnterior, int *map, int atual);

    int mapeamento(int *map, int id);

    //methods phase1
    float greed();

    float greedRandom();

    float greedRactiveRandom();

    //axiliar methods
    void printGraph();

    void printGraphDot(ofstream &file);

    void
    dfsRec(int id, list<Edge> &arvore, list<Edge> &retorno, int *pai, int tempo, int *tempoDescoberta, int *tempoFinal);

    void minimalPathByFloyd(int id_one, int id_two);

    void minimalSpanningTreeByPrimAlgorithm(Graph *g);

private:
    //Auxiliar methods
    bool searchListAdj(int idNode, int idToFind);

    int countNodeInAdjList(int idNode, int idToFind);

    bool arestaNaLista(Aresta_aux listEdges[], int id, int destino, int size);

    void cleanVisited();

    int getNumberInMap(int id, std::map<Node *, int> m);

    EdgeLinkedNode *getLighterEdge(list<Node *> t, list<Node *> v);
};
*/


#endif //GRAFO_H_INCLUDED