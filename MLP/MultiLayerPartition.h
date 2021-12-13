//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H

#include "../PUNCH/Filter/G_Graph.h"
#include "../PUNCH/Assemble/A_Graph.h"
#include "../Common/sw_basetypes.h"
#include "../Common/tp_basetype.h"
#include "../Common/Utility.h"
#include "../Common/crp_types.h"

#include "Assembly.h"
#include "Filter.h"
#include "GraphPrinter.h"
#include "Preprocess.h"
//#include "AdaptivePrinter.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <streambuf>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <unordered_set>

using namespace std;

class MultiLayerPartition {
private:
    int L, U, Uf, C, FI, M, PS;
    const string paraPath;
    const string outPath;
    const NodeID nodeNum;
    vector<vector<vector<NodeID>>> cells_edges;
    vector<vector<NodeID>> cells_nodes;
    vector<vector<vector<NodeID>>> res_cells_edges;
    vector<vector<NodeID>> res_cells_nodes;
    vector<vector<NodeID>> void_cells;
    vector<vector<uint8_t>> node_parti;
    vector<size_t> cell_sizes;
    bool phantom;

    void MLP();
    void read_graph(const string topo_node_path, const string topo_weight_path);
    void print_parti(const string timestamp);

public:
    const int ParaNum = 5;
    vector<vector<int>> parameters;

    MultiLayerPartition(const string pPath, const string oPath, const NodeID node_num, bool isPhantom):
        paraPath(pPath), outPath(oPath), nodeNum(node_num), phantom(isPhantom){};
    ~MultiLayerPartition() = default;
    void generateMLP() {
        this->MLP();
    }
    int getL(){return L;}
    void setL(int l){L = l;}
    vector<vector<NodeID>>& get_void_cells() {return void_cells;}
};

#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H
