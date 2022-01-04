/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <vector>

using namespace std;

class Graph{

    //Atributes
    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        Node* first_node;
        Node* last_node;
        // Para auxiliar na indexação interna dos nós
        int lastIdUsed;

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
        Node* getFirstNode();
        Node* getLastNode();
        //Other methods
        void insertNode(int id, int name);
        void insertEdge(int name, int target_name, float weight);
        void removeNode(int id);
        bool searchNode(int name);
        bool searchNodeById(int id);
        Node* getNode(int name);
        Node* getNodeById(int id);

        //methods phase1
        void topologicalSorting();
        void breadthFirstSearch(int name, ofstream& output_file);
        void getVertexInducedDirectTransitiveClosure(int name, ofstream& output_file);
        void getVertexInducedIndirectTransitiveClosure(int name, ofstream& output_file);
        Graph* algoritmoKruskal(int* vertices);
        Graph* algoritmoPrim(int* vertices);
        void floydWarshall(int nameSource, int nameTarget, ofstream& output_file);
        void dijkstra(int nameSource, int nameTarget, ofstream& output_file);

        //methods phase1
        //float greed();
        //float greedRandom();
        //float greedReactiveRandom();
    private:
        //Auxiliar methods
        void generatesDotLanguage(int pred[], ofstream& output_file);
        void auxTopologycalSorting(int* time, int discovered[], int visited[], int predecessors[], int ind, int finished[], int topSort[], int* indArray, bool* ehCiclico);
        bool find(vector <int> myVector, int wanted);
};

#endif // GRAPH_H_INCLUDED
