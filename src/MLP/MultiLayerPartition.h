//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H

#include "../PUNCH/Filter/G_Graph.h"
#include "../PUNCH/Assemble/A_Graph.h"
#include "../../common/sw_basetypes.h"
#include "../../common/tp_basetype.h"
#include "../../common/Utility.h"
#include "../../common/base_def.h"
#include "../../common/crp_types.h"

#include "Assembly.h"
#include "Filter.h"
#include "GraphPrinter.h"
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
    NodeSize nodeNum;
    vector<vector<NodeID>> cells_edges;
    vector<vector<NodeID>> cells_nodes;
    vector<vector<NodeID>> res_cells_edges;
    vector<vector<NodeID>> res_cells_nodes;
    vector<vector<NodeID>> void_cells;
    vector<vector<NodeID>> node_parti;
    vector<NodeSize> cell_sizes;
    bool phantom;
    bool accumulate = true;

    void MLP();

public:
    const int ParaNum = 5;
    vector<vector<int>> parameters;

    MultiLayerPartition(const string pPath, const string oPath, bool isPhantom):
        paraPath(pPath), outPath(oPath), phantom(isPhantom){};
    ~MultiLayerPartition() = default;
    void generateMLP() {
        this->MLP();
    }
    void read_topo_graph(const string topo_weight_path);
    void read_base_graph(const string base_node_path, const string base_link_path);
    void read_accumu_parti(const string parti_path, const int base_layer);
    void print_parti(const string timestamp);
    int getL(){return L;}
    void setL(int l){L = l;}
    vector<vector<NodeID>>& get_void_cells() {return void_cells;}
};

#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MULTILAYERPARTITION_H
