/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Edge{

    // Attributes
    private:
        int target_id;
        int target_name;
        Edge* next_edge;
        float weight;

    public:
        // Constructor
        Edge(int target_id, int target_name);
        // Destructor
        ~Edge();
        // Getters
        int getTargetName();
        int getTargetId();
        Edge* getNextEdge();
        float getWeight();
        // Setters
        void setNextEdge(Edge* edge);
        void setWeight(float weight); 

}; 

#endif // EDGE_H_INCLUDED