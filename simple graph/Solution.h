//
// Created by lucia on 06/02/2022.
//

#ifndef GRAPH_THEORY_SOLUTION_H
#define GRAPH_THEORY_SOLUTION_H


#include <iostream>
#include <vector>
#include "Cluster.h"
#include "Node.h"


using namespace std;

class Solution{
private:
    unsigned int totalGAP;
    int n_clusters;
    int n_nodes;
    vector<Cluster*> clusters;

public:
    Solution(int n_clusters, int n_nodes, int uppLimit);
    ~Solution();
    bool checkViability(int** costPaths, int rows);
    vector<Cluster*> getClusters();
    Cluster* getClusterById(int id);
    void addNodeCluster(int node, int nodeWeight, int cluster);
    unsigned int getTotalGAP();
    void printClustersInSolution(ofstream& file);
    void updateGAP();
};



#endif //GRAPH_THEORY_SOLUTION_H
