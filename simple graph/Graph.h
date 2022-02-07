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
#include "Solution.h"
#include "NodeCluster.h"
#include "Cluster.h"


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
        int num_clusters;
        // Para auxiliar na indexação interna dos nós
        int lastIdUsed;

    public:
        //Constructor
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node, int clusters);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();
        int getNumClusters();
        Node* getFirstNode();
        Node* getLastNode();
        int getLastIdUsed();
        void setLastIdUsed(int newLastId);
        //Other methods
        void insertNode(int id, int name, int weight);
        void insertEdge(int name, int target_name, int weight);
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
        int** floydWarshall(int nameSource, int nameTarget, ofstream& output_file);
        void dijkstra(int nameSource, int nameTarget, ofstream& output_file);

        //methods phase2
        Solution* greedy();
        Solution* greedyRandom(float alpha, int numIt);
        Solution* greedReactiveRandom(float* alphas, int numIt, int bloco, int numAlphas);
    private:
        //Auxiliar methods
        void generatesDotLanguage(int pred[], ofstream& output_file);
        void auxTopologycalSorting(int* time, int discovered[], int visited[], int predecessors[], int ind, int finished[], int topSort[], int* indArray, bool* ehCiclico);
        bool find(vector <int> myVector, int wanted);

        // methods phase2
        void fillCandidatesList(vector<NodeCluster*> *candidatesList, Solution *sol);
        void preProcessing(Solution* sol, vector<NodeCluster*>* candidatesList);
        void sortCandidatesList(vector<NodeCluster*>* candidatesList);
        void updateCandidatesListCaseCluster(vector<NodeCluster*> *candidatesList, int clusterId);
        void updateCandidatesListCaseNode(vector<NodeCluster*> *candidatesList, int nodeId);
        void updateCandidatesListQuotioent(vector<NodeCluster*>* candidatesList);
        int randomInteger(int low, int high);
        void vectorInitialization(float *P, float *A, float *S, float *Q, int numAlphas);
        void updateProbabilities(float *P, float *A, Solution* solBest, int numAlphas);
        int chooseAlpha(float *P, int numAlphas);
        void updateAverages(float *A, float *S, float *Q, Solution* sol, int alpha);
};

#endif // GRAPH_H_INCLUDED
