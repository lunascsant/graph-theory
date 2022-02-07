//
// Created by lucia on 06/02/2022.
//

#include "NodeCluster.h"
#include "constants.h"

using namespace std;


NodeCluster::NodeCluster(){

}

NodeCluster::~NodeCluster() {

}

NodeCluster::NodeCluster(Node* node, Cluster* cluster) {
    this->node = node;
    this->cluster = cluster;
    this->calcQuotient();
}

Node *NodeCluster::getNode() {
    return this->node;
}

Cluster *NodeCluster::getCluster() {
    return this->cluster;
}

void NodeCluster::calcQuotient() {
    int newGap;
    int numAdj = this->numAdj();
    if(numAdj != 0){
        if ((this->node->getWeight() > this->cluster->getMinValue()) && (this->node->getWeight() < this->cluster->getMaxValue())){
            this->quotient = this->cluster->getGap() / numAdj;
        } else if (this->node->getWeight() < this->cluster->getMinValue()){
            newGap = this->cluster->getMaxValue() - this->node->getWeight();
            this->quotient = newGap / numAdj;
        } else if (this->node->getWeight() > this->cluster->getMaxValue()){
            newGap = this->node->getWeight() - this->cluster->getMinValue();
            this->quotient = newGap / numAdj;
        }
    } else if(numAdj == 0){
        this->quotient = INFINITY;
    }
}

int NodeCluster::numAdj() {
    int numAdj = 0;

    if (this->cluster->qtyNodes() == 0) {
        numAdj = 0;
    } else {
        for (int i = 0; i < this->cluster->qtyNodes(); i++) {
            numAdj += this->node->searchEdge(this->cluster->getIdNode(i));
        }
    }

    return numAdj;
}

float NodeCluster::getQuotient() {
    return this->quotient;
}
