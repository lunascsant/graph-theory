//
// Created by lucia on 06/02/2022.
//

#include "Cluster.h"

using namespace std;

Cluster::Cluster(int id, int uppLimit) {
    this->id = id;
    this->maxValue = 0;
    this->minValue = 0;
    this->uppLimit = uppLimit;
    this->gap = 0;
}

Cluster::~Cluster() {

}

int Cluster::getMaxValue() {
    return this->maxValue;
}

int Cluster::getMinValue() {
    return this->minValue;
}

int Cluster::getGap() {
    return this->gap;
}

void Cluster::setMaxValue(int newMax) {
    this->maxValue = newMax;
}

void Cluster::setMinValue(int newMin) {
    this->minValue = newMin;
}

void Cluster::addNode(int idNode, int weightOfNode) {
    if (this->nodes.size() < this->uppLimit) {
        this->nodes.push_back(idNode);
    }

    int analysedNodeWeight = weightOfNode;

    if(this->maxValue == 0 && this->minValue == 0){
        setMaxValue(analysedNodeWeight);
        setMinValue(analysedNodeWeight);
    }
    else if(analysedNodeWeight > this->maxValue)
    {
        setMaxValue(analysedNodeWeight);
        this->updateGap();
    }
    else if(analysedNodeWeight < this->minValue)
    {
        setMinValue(analysedNodeWeight);
        this->updateGap();
    }
}

void Cluster::updateGap()
{
    if(this->nodes.size() == 1) {
        this->gap = 0;
    } else {
        this->gap = this->maxValue - this->minValue;
    }

}

int Cluster::qtyNodes() {
    return this->nodes.size();
}

int Cluster::getIdNode(int index) {
    return this->nodes[index];
}

vector<int> Cluster::getListNodes() {
    return this->nodes;
};

int Cluster::getId(){
    return this->id;
}