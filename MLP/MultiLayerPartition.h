//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H

#include "../PUNCH/Filter/G_Graph.h"
#include "../PUNCH/Assemble/A_Graph.h"
#include "Assembly.h"
#include "Filter.h"
#include "GraphPrinter.h"
#include "Preprocess.h"
#include "AdaptivePrinter.h"
//#include "PostProgress.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <streambuf>

using namespace std;

class MultiLayerPartition {
private:
    int L = 1;
    void MLP();
    const string paraPath;
    const string outPath;
    const unsigned int nodeNum;
    bool phantom;
public:
    const int ParaNum = 5;
    vector<vector<int>> parameters;

    MultiLayerPartition(const string pPath, const string oPath, const unsigned int node_num, bool isPhantom):
        paraPath(pPath), outPath(oPath), nodeNum(node_num), phantom(isPhantom){};
    ~MultiLayerPartition() = default;
    void generateMLP() {
        this->MLP();
    }
    int getL(){return L;}
    void setL(int l){L = l;}
};

#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H
