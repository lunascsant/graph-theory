//
// Created by lucia on 06/02/2022.
//

#ifndef GRAPH_THEORY_NODECLUSTER_H
#define GRAPH_THEORY_NODECLUSTER_H

#include "Node.h"
#include "Cluster.h"

class NodeCluster {
private:
    Node* node;
    Cluster* cluster;
    float quotient;
    int numAdj();
public:
    NodeCluster();
    ~NodeCluster();
    NodeCluster(Node* node, Cluster* cluster);
    Node* getNode();
    Cluster* getCluster();
    float getQuotient();
    void calcQuotient();
};


#endif //GRAPH_THEORY_NODECLUSTER_H
