//
// Created by lucia on 06/02/2022.
//

#include "Solution.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include "Cluster.h"
#include "constants.h"

using namespace std;

Solution::Solution(int n_clusters, int n_nodes, int uppLimit)
{
    this->n_clusters = n_clusters;
    this->n_nodes = n_nodes;
    this->totalGAP = 0;

    for (int i = 0; i < n_clusters; i++) {
        this->clusters.push_back(new Cluster(i, uppLimit));
    }
}

Solution::~Solution()
{
    for (int i = 0; i < n_clusters; i++) {
        delete this->clusters.at(i);
    }
}

/*
 * observações:
 * - se o grafo não é direcionado podemos otimizar a verificação do custo
 */

bool Solution::checkViability(int** costPaths, int rows)
{
    bool viable = 1;
    int indRow, indCol;

    for(int i = 0; (i < this->n_clusters) && (viable); i++) {
        Cluster* currentCluster = this->clusters.at(i);
        for(int j = 0; (j < currentCluster->qtyNodes()) && (viable); j++) {
            indRow = currentCluster->getIdNode(j);
            for(int k = 0; (k < currentCluster->qtyNodes()) && (viable); k++) {
                indCol = currentCluster->getIdNode(k);
                if(costPaths[indRow][indCol] == INFINITY) {
                    // não é viável
                    viable = 0;
                }
            }
        }
    }

    for (int i = 0; i < rows; ++i)
        delete [] costPaths[i];
    delete [] costPaths;

    return viable;
}

vector<Cluster*> Solution::getClusters()
{
    return this->clusters;
}

Cluster* Solution::getClusterById(int id) {
    return this->clusters.at(id);
}

void Solution::addNodeCluster(int node, int nodeWeight, int cluster) {
   this->clusters.at(cluster)->addNode(node, nodeWeight);
   this->updateGAP();
}

unsigned int Solution::getTotalGAP() {
    updateGAP();
    return this->totalGAP;
}

void Solution::updateGAP() {
    for (int i = 0; i < this->n_clusters; i++)
    {
        this->totalGAP += this->clusters.at(i)->getMaxValue() - this->clusters.at(i)->getMinValue();
    }
}

void Solution::printClustersInSolution(ofstream& file){
    float wbGAPTotal = 0;
    for (int i = 0; i < this->n_clusters; i++)
    {
        file<<"Cluster "<< i <<":"<<endl;
        for (int j = 0; j < this->clusters.at(i)->qtyNodes(); j++)
        {
            file<<this->clusters.at(i)->getListNodes().at(j)<<",   ";
        }
        file<<endl;
        file<<"Max value: "<< this->clusters.at(i)->getMaxValue()<<endl;
        file<<"Min value: "<< this->clusters.at(i)->getMinValue()<<endl;
        file<<"QTD nodes cluster = " << this->clusters.at(i)->getListNodes().size()<<endl;
        file<<"SB GAP = " << this->clusters.at(i)->getMaxValue() - this->clusters.at(i)->getMinValue()<<endl;
        file<<"IS GAP = " << this->clusters.at(i)->getGap()<<endl;
        wbGAPTotal += this->clusters.at(i)->getMaxValue() - this->clusters.at(i)->getMinValue();
        file<<"\n\n";
    }

    file<<"WB GAP TOTAL = "<<wbGAPTotal<<endl;
}

