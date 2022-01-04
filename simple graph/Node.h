/**************************************************************************************************
 * Implementation of the TAD Node
**************************************************************************************************/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h" // Include of the Edge class

using namespace std;

// Definition of the Node class
class Node{

    // Attributes
    private:
        Edge* first_edge;
        Edge* last_edge;
        // esse atributo id é uma identidade interna para manipulação do grafo
        int id;
        unsigned int in_degree;
        unsigned int out_degree;
        float weight;
        Node* next_node;
        // esse atributo é o número que aparece nas instâncias
        int name;

    public:
        // Constructor
        Node(int id, int name);
        // Destructor
        ~Node();
        // Getters
        Edge* getFirstEdge();
        Edge* getLastEdge();
        int getId();
        int getName();
        int getInDegree();
        int getOutDegree();
        float getWeight();
        Node* getNextNode();
        // Setters
        void setNextNode(Node* node);
        void setWeight(float weight);
        // Other methods
        bool searchEdge(int target_name);
        bool searchEdgeById(int target_name);
        void insertEdge(int target_id, int target_name, float weight);
        void removeAllEdges();
        int removeEdge(int id, bool directed, Node* target_node);
        void incrementOutDegree();
        void decrementOutDegree();
        void incrementInDegree();
        void decrementInDegree();
        Edge* hasEdgeBetween(int target_name);
        // Auxiliar methods

};

#endif // NODE_H_INCLUDED
