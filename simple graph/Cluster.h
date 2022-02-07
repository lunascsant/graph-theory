//
// Created by lucia on 06/02/2022.
//

#ifndef GRAPH_THEORY_CLUSTER_H
#define GRAPH_THEORY_CLUSTER_H

#include <vector>

using namespace std;

class Cluster {
private:
    int id;
    vector<int> nodes;
    int maxValue;
    int minValue;
    int gap;
    int uppLimit;

    void updateGap();
public:
    Cluster(int id, int uppLimit);
    ~Cluster();
    int getMaxValue();
    int getMinValue();
    int getGap();
    void setMaxValue(int newMax);
    void setMinValue(int newMin);
    void addNode(int idNode, int weightOfNode);
    int qtyNodes();
    int getIdNode(int index);
    int getId();
    vector<int> getListNodes();
};


#endif //GRAPH_THEORY_CLUSTER_H
