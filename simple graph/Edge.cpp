#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Edge's methods
**************************************************************************************************/

// Constructor
Edge::Edge(int target_id, int target_name, int weight){

    this->target_name = target_name;
    this->target_id = target_id;
    this->next_edge = nullptr;
    this->weight = weight;

}

// Destructor
Edge::~Edge(){

    if (this->next_edge != nullptr){
        delete this->next_edge;
        this->next_edge = nullptr;
    }

}

// Getters
int Edge::getTargetName(){

    return this->target_name;

}

int Edge::getTargetId(){

    return this->target_id;

}


Edge* Edge::getNextEdge(){

    return this->next_edge;

}

int Edge::getWeight(){

    return this->weight;

}

// Setters
void Edge::setNextEdge(Edge* edge){

    this->next_edge = edge;

}

void Edge::setWeight(int weight){

    this->weight = weight;

}
