//
// Created by 骏辉 on 2021/10/19.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ADAPTIVEPRINTER_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ADAPTIVEPRINTER_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "../Common/sw_basetypes.h"
#include "../Common/common.h"

using namespace std;

class AdaptivePrinter {
private:
    const string out_path;
    vector<int> cell_nums;
    const int layer;
    const NodeID node_num;
    vector<vector<int>> node_parti;
    vector<vector<unsigned int>> phantom_nodes;
    void read_phantom_nodes();

public:
    AdaptivePrinter(const string o_path, const int l, const NodeID n_num): out_path(o_path), layer(l), node_num(n_num){cell_nums.resize(l);}
    void print_final_result();
    void print_result_for_show(const string node_path, const string edge_path);
    void filter_result();
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ADAPTIVEPRINTER_H
