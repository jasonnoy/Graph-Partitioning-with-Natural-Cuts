//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H

#include "../Filter/G_Graph.h"
#include "../Assemble/A_Graph.h"
#include "../Assemble/R_Graph.h"
#include "Assembly.h"
#include "Filter.h"
#include "GraphPrinter.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

class MultiLayerPartition {
private:
    int L = 1;
    void MLP();
    const string paraPath;
    const string coPath;
    const string grPath;
    const string outPath;
    const unsigned int nodeNum;
    const bool phantom;
public:
    const int ParaNum = 5;
    vector<vector<int>> parameters;

    MultiLayerPartition(const string pPath, const string nPath, const string gPath, const string oPath, const bool isPhantom):
        paraPath(pPath), coPath(nPath), grPath(gPath), outPath(oPath), phantom(isPhantom){};
    ~MultiLayerPartition() = default;
    void generateMLP() {
        this->MLP();
    }
    int getL(){return L;}
    void setL(int l){L = l;}
};

#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H
