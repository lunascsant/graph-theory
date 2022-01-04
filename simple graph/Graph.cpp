#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <vector>
#include <iterator>
#include <climits>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{
    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
    this->lastIdUsed = -1;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}


Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id, int name)
{
    if(!searchNode(name)) {
        Node* newNode = new Node(id, name);
        if(first_node == nullptr) {
            first_node = newNode;
        } else {
            last_node->setNextNode(newNode);
        }
        last_node = newNode;
    }

}

void Graph::insertEdge(int name, int target_Name, float weight)
{
    //cout << "----------------- INSERINDO -----------------" << endl;
    Node* nodeOrigem = getNode(name);
    Node* nodeDestino = getNode(target_Name);

    if(nodeOrigem != nullptr && nodeDestino != nullptr) {
        // cout << "Vem nos dois existentes" << endl;
        nodeOrigem->insertEdge(nodeDestino->getId(), target_Name, weight);

        // Verifico se meu grafo é direcionado, pois se for, não tenho que colocar adjacência dos dois lados
        if(!directed) {
            nodeDestino->insertEdge(nodeOrigem->getId(), name, weight);
        }

        number_edges++;
    } else if (nodeOrigem != nullptr && nodeDestino == nullptr){
        // cout << "Vem no destino null" << endl;
        lastIdUsed++;
        this->insertNode(lastIdUsed, target_Name);
        Node* newNodeDestino = getNode(target_Name);
        nodeOrigem->insertEdge(newNodeDestino->getId(), target_Name, weight);

        // Verifico se meu grafo é direcionado, pois se for, não tenho que colocar adjacência dos dois lados
        if(!directed) {
            newNodeDestino->insertEdge(nodeOrigem->getId(), name, weight);
        }

        number_edges++;
    } else if (nodeOrigem == nullptr && nodeDestino != nullptr){
        // cout << "Vem no origem null" << endl;
        lastIdUsed++;
        this->insertNode(lastIdUsed, name);
        Node* newNodeOrigem = getNode(name);

        newNodeOrigem->insertEdge(nodeDestino->getId(), target_Name, weight);


        // Verifico se meu grafo é direcionado, pois se for, não tenho que colocar adjacência dos dois lados
        if(!directed) {
            nodeDestino->insertEdge(newNodeOrigem->getId(), name, weight);
        }

        number_edges++;
    } else {
        // cout << "Vem nos dois null " << endl;
        lastIdUsed++;
        this->insertNode(lastIdUsed, name);
        Node* newNodeOrigem = getNode(name);
        lastIdUsed++;
        this->insertNode(lastIdUsed, target_Name);
        Node* newNodeDestino = getNode(target_Name);

        newNodeOrigem->insertEdge(newNodeDestino->getId(), target_Name, weight);


        // Verifico se meu grafo é direcionado, pois se for, não tenho que colocar adjacência dos dois lados
        if(!directed) {
            newNodeDestino->insertEdge(newNodeOrigem->getId(), name, weight);
        }

        number_edges++;
    }

    // cout << "----------------- INSERINDO x FIM -----------------" << endl;
}

void Graph::removeNode(int id){ 
    // Implementar se necessário
}

bool Graph::searchNode(int name)
{
    if(first_node != nullptr) {
        for(Node* node = first_node; node != nullptr; node = node->getNextNode()) {
            if(node->getName() == name) {
                return true;
            }
        }
    }

    return false;
}

bool Graph::searchNodeById(int id)
{
    if(first_node != nullptr) {
        for(Node* node = first_node; node != nullptr; node = node->getNextNode()) {
            if(node->getId() == id) {
                return true;
            }
        }
    }

    return false;
}

Node *Graph::getNode(int name)
{
    if(first_node != nullptr) {
        for(Node* node = first_node; node != nullptr; node = node->getNextNode()) {
            if(node->getName() == name) {
                return node;
            }
        }
    }

    return nullptr;
}

Node *Graph::getNodeById(int id)
{
    if(first_node != nullptr) {
        for(Node* node = first_node; node != nullptr; node = node->getNextNode()) {
            if(node->getId() == id) {
                return node;
            }
        }
    }

    return nullptr;
}

void Graph::getVertexInducedDirectTransitiveClosure(int name, ofstream& output_file) {
    if (this->getDirected()){
        int v = this->getOrder();
        bool trans[v][v];
        vector <int> subgraphNodes;
        vector <int> subgraphNodesNames;

        Node* auxNodeSource = this->getNode(name);
        int sourceId = auxNodeSource->getId();


        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (i == j) {
                    trans[i][j] = 1;
                }
                else {
                    trans[i][j] = 0;
                }
            }
        }


        for(Node* node = this->getFirstNode(); node != nullptr; node = node->getNextNode()) {
            for(Edge* adjNode = node->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
                trans[node->getId()][adjNode->getTargetId()] = 1;
            }
        }



        for(int k = 0; k < v; k++) {
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    trans[i][j] = (trans[i][j]) || (trans[i][k] && trans[k][j]);
                }
            }
        }

        for (int i = 0; i < v; i++) {
            if(trans[sourceId][i] == 1)
            subgraphNodes.push_back(i);
        }

        Node* auxNode;
        int auxName;

        for (int i = 0; i < subgraphNodes.size(); i++) {
            auxNode = this->getNodeById(subgraphNodes[i]);
            auxName = auxNode->getName();
            subgraphNodesNames.push_back(auxName);
        }

        output_file << "digraph Grafo {\n";
        for(int i = 0; i < subgraphNodesNames.size(); i++) {
            auxNode = this->getNode(subgraphNodesNames[i]);
            for(Edge* adjNode = auxNode->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
                if(find(subgraphNodesNames, adjNode->getTargetName())) {
                    output_file << subgraphNodesNames[i] << " -> " << adjNode->getTargetName() << ";\n";
                }
            }
        }
        output_file << "}";

    } else {
        cout << "Grafo nao direcionado" << endl;
    }
}


void Graph::getVertexInducedIndirectTransitiveClosure(int name, ofstream& output_file) {
    if (this->getDirected()){
        int v = this->getOrder();
        bool trans[v][v];
        vector <int> subgraphNodes;
        vector <int> subgraphNodesNames;

        Node* auxNodeSource = this->getNode(name);
        int sourceId = auxNodeSource->getId();


        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (i == j) {
                    trans[i][j] = 1;
                }
                else {
                    trans[i][j] = 0;
                }
            }
        }


        for(Node* node = this->getFirstNode(); node != nullptr; node = node->getNextNode()) {
            for(Edge* adjNode = node->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
                trans[node->getId()][adjNode->getTargetId()] = 1;
            }
        }



        for(int k = 0; k < v; k++) {
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    trans[i][j] = (trans[i][j]) || (trans[i][k] && trans[k][j]);
                }
            }
        }

        for (int i = 0; i < v; i++) {
            if(trans[i][sourceId] == 1)
                subgraphNodes.push_back(i);
        }

        Node* auxNode;
        int auxName;

        for (int i = 0; i < subgraphNodes.size(); i++) {
            auxNode = this->getNodeById(subgraphNodes[i]);
            auxName = auxNode->getName();
            subgraphNodesNames.push_back(auxName);
        }

        output_file << "digraph Grafo {\n";
        for(int i = 0; i < subgraphNodesNames.size(); i++) {
            auxNode = this->getNode(subgraphNodesNames[i]);
            for(Edge* adjNode = auxNode->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
                if(find(subgraphNodesNames, adjNode->getTargetName())) {
                    output_file << subgraphNodesNames[i] << " -> " << adjNode->getTargetName() << ";\n";
                }
            }
        }
        output_file << "}";

    } else {
        cout << "Grafo nao direcionado" << endl;
    }
}

//Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(int name, ofstream& output_file) {
    // Vetores auxiliares com distância e predecessor de cada nó na busca em largura
    // O indice do vetor corresponde a id do nó
    int tam = this->getOrder();
    int visited[tam]; // se foi visitado completamente -> 1, parcialmente -> 0, não foi visitado -> -1
    int distances[tam];
    int predecessors[tam];

    int ind = -1;
    for(Node* node = this->getFirstNode(); node != nullptr; node = node->getNextNode()) {
        ind = node->getId();
        visited[ind] = -1;
        distances[ind] = tam + 1;
        predecessors[ind] = -1;
    }


    Node* firstNodeSearch = this->getNode(name);
    ind = firstNodeSearch->getId();
    visited[ind] = 0;
    distances[ind] = 0;
    queue<int> visitationQueue;
    visitationQueue.push(ind);

    int idNodeBeingUsed;
    int idAdjNode;
    Node* nodeBeingUsed;
    while(!visitationQueue.empty()) {
        idNodeBeingUsed = visitationQueue.front();
        nodeBeingUsed = this->getNodeById(idNodeBeingUsed);
        visitationQueue.pop();
        for(Edge* adjNode = nodeBeingUsed->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
            idAdjNode = adjNode->getTargetId();
            if(visited[idAdjNode] == -1) {
                visited[idAdjNode] = 0;
                distances[idAdjNode] = distances[idNodeBeingUsed] + 1;
                predecessors[idAdjNode] = idNodeBeingUsed;
                visitationQueue.push(idAdjNode);
            }
        }
        visited[idNodeBeingUsed] = 1;
    }


    this->generatesDotLanguage(predecessors, output_file);
}



void Graph::floydWarshall(int nameSource, int nameTarget, ofstream& output_file) {
    int v = this->getOrder();
    int dist[v][v];
    int pred[v][v];
    vector<int> visited;

    Node* auxNodeSource = this->getNode(nameSource);
    int sourceId = auxNodeSource->getId();
    Node* auxNodeTarget = this->getNode(nameTarget);
    int targetId = auxNodeTarget->getId();


    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (i == j) {
                dist[i][j] = 0;
            }
            else {
                dist[i][j] = 1000000; // isso invalida arestas com peso maior que 1000000
            }
            pred[i][j] = -1;
        }
    }


    for(Node* node = this->getFirstNode(); node != nullptr; node = node->getNextNode()) {
        for(Edge* adjNode = node->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
            dist[node->getId()][adjNode->getTargetId()] = adjNode->getWeight();
            pred[node->getId()][adjNode->getTargetId()] = node->getId();
        }
    }



    for(int k = 0; k < v; k++) {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if(dist[i][j] > (dist[i][k] + dist[k][j])) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }

            }
        }
    }


    visited.push_back(targetId);
    int n = targetId;
    while(n != sourceId) {
        visited.push_back(pred[sourceId][n]);
        n = pred[sourceId][n];
    }


    int size = visited.size() - 1;
    Node* auxNode = this->getNodeById(visited[size]);
    output_file << "strict graph Grafo {\n";
    output_file << auxNode->getName();
    for (int i = size - 1; i >= 0; i--) {
        output_file << " -- ";
        auxNode = this->getNodeById(visited[i]);
        output_file << auxNode->getName();
    }
    output_file << "; \n}";

    cout << "O custo do caminho minimo: " << dist[sourceId][targetId] << endl;

}

   

void Graph::dijkstra(int nameSource, int nameTarget, ofstream& output_file) {
    vector <int> visitable;
    vector <int> visited;
    int tam = this->getOrder();
    int costs[tam];
    int pred[tam];
    int minCost = 1000000;
    int remainingNodes = tam - 1;
    int currentNodeId;

    Node* sourceNode = getNode(nameSource);
    Node* targetNode = getNode(nameTarget);

    // inicializando S e -S e os custos
    // visited.push_back(sourceNode->getId());
    costs[sourceNode->getId()] = 0;

    for(int i = 0; i < tam; i++) {
        if (i != sourceNode->getId()) {
            visitable.push_back(i);
            costs[i] = INT_MAX;
            pred[i] = -1;
        }
    }

    // colocando o custo dos adjacentes
    for(Edge* adjNode = sourceNode->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
        costs[adjNode->getTargetId()] = adjNode->getWeight();
    }

    currentNodeId = sourceNode->getId();
    while(remainingNodes > 0) {
        minCost = costs[visitable[0]];
        currentNodeId = visitable[0];
        for(int i = 1; i < visitable.size(); i++) {
            if(costs[visitable[i]] <= minCost) {
                minCost = costs[visitable[i]];
                currentNodeId = visitable[i];
            }
        }

        for(int i = 0; i < visitable.size(); i++) {
            if(visitable[i] == currentNodeId) {
                visitable.erase(visitable.begin() + i);
                remainingNodes--;
                break;
            }
        }


        Node* currentNode = getNodeById(currentNodeId);
        for(Edge* adjNode = currentNode->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
            if(find(visitable, adjNode->getTargetId())) {
                int c;
                c = costs[adjNode->getTargetId()];
                if ((costs[currentNodeId] + adjNode->getWeight()) < c) {
                    costs[adjNode->getTargetId()] = costs[currentNodeId] + adjNode->getWeight();
                    pred[adjNode->getTargetId()] = currentNodeId;
                }
            }
        }
    }

    visited.push_back(targetNode->getId());
    int n = targetNode->getId();
    while(n != -1) {
        if (pred[n] != -1)
            visited.push_back(pred[n]);
        n = pred[n];
    }
    visited.push_back(sourceNode->getId());

    int size = visited.size() - 1;
    Node* auxNode = this->getNodeById(visited[size]);
    output_file << "strict graph Grafo {\n";
    output_file << auxNode->getName();
    for (int i = size - 1; i >= 0; i--) {
        output_file << " -- ";
        auxNode = this->getNodeById(visited[i]);
        output_file << auxNode->getName();
    }
    output_file << "; \n}";


    cout << "O custo do caminho minimo: " << costs[targetNode->getId()] << endl;


}

bool Graph::find(vector <int> myVector, int wanted) {
    for (int i = 0; i < myVector.size(); i++) {
        if(myVector[i] == wanted)
            return true;
    }

    return false;
}

//function that prints a topological sorting
void Graph::topologicalSorting() {
    if(this->getDirected()) {
        bool ehCiclico = 0;
        // Vetores auxiliares com visitação, predecessor, descoberto e finalizado de cada nó na busca em profundidade
        // O indice do vetor corresponde a id do nó
        int tam = this->getOrder();
        int visited[tam]; // se foi visitado completamente -> 1, parcialmente -> 0, não foi visitado -> -1
        int predecessors[tam];
        // marcação de tempo
        int discovered[tam];
        int finished[tam];
        int time = 0;

        // array com a ordenação
        int indArray = 0;
        int topSort[tam];

        int ind = -1;
        for(Node* node = this->getFirstNode(); node != nullptr; node = node->getNextNode()) {
            ind = node->getId();
            visited[ind] = -1;
            predecessors[ind] = -1;
        }


        for(Node* node = this->getFirstNode(); node != nullptr; node = node->getNextNode()) {
            ind = node->getId();
            if (visited[ind] = -1) {
                this->auxTopologycalSorting(&time, discovered, visited, predecessors, ind, finished, topSort, &indArray, &ehCiclico);
            }
        }


        if(ehCiclico) {
            cout << "Este grafo possui ciclo." << endl;
        } else {
            Node* auxNode;
            cout << "xxxxxxxxxx ORDENACAO TOPOLOGICA DO GRAFO xxxxxxxxxxx\n";
            for (int i = 0; i < tam; i++) {
                auxNode = getNodeById(i);
                cout << auxNode->getName() << " ";
            }
            cout << endl << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        }

    } else {
        cout << "O grafo nao eh direcionado" << endl;
    }

}

void Graph::auxTopologycalSorting(int* time, int discovered[], int visited[], int predecessors[], int ind, int finished[], int topSort[], int* indArray, bool* ehCiclico) {
    *time = *time + 1;
    discovered[ind] = *time;
    visited[ind] = 0;

    Node* nodeBeingUsed;
    int idAdjNode;
    nodeBeingUsed = this->getNodeById(ind);
    for(Edge* adjNode = nodeBeingUsed->getFirstEdge(); adjNode != nullptr; adjNode = adjNode->getNextEdge()) {
        idAdjNode = adjNode->getTargetId();
        if(visited[idAdjNode] == -1) {
            predecessors[idAdjNode] = ind;
            auxTopologycalSorting(time, discovered, visited, predecessors, idAdjNode, finished, topSort, indArray, ehCiclico);
        } else if (visited[idAdjNode] == 0) {
            // yields a back edge, cyclic graph
            // cout << "Grafo ciclico." << endl;
            *ehCiclico = 1;
        }
    }

    visited[ind] = 1;
    *time = *time + 1;
    finished[ind] = *time;
    topSort[*indArray] = ind;
    *indArray = *indArray + 1;
}

/*
Graph* Graph::algoritmoKruskal(int* vertices) {

}

Graph* Graph::algoritmoPrim(int* vertices) {

}*/

void Graph::generatesDotLanguage(int pred[], ofstream& output_file) {
    Node* auxNode;
    Node* auxPred;
    output_file << "strict graph Grafo {\n";
    for (int i = 0; i < this->getOrder(); i++) {
        if (pred[i] != -1) {
            auxNode = this->getNodeById(i);
            auxPred = this->getNodeById(pred[i]);
            output_file << auxPred->getName() << " -- " << auxNode->getName() << ";\n";
        }
    }
    output_file << "}";
}
