//
// Created by 骏辉 on 2021/10/14.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H

#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#include "../Common/common.h"

class GraphPrinter {
private:
    const int l;
    vector<NodeID>& cell_edges;
    const vector<NodeID>& void_nodes;
//    vector<NodeID> cell_nodes;
    const vector<vector<NodeID>>& id_map;
    const vector<NodeID>& real_map;
    const vector<vector<NodeID>>& a_result;
    vector<vector<NodeID>> phantom_nodes;
    vector<vector<NodeID>> result_cuts;

    // 替代无用引用成员参数, only for replacing members with empty vecs
    vector<NodeID> replace_vec;
    vector<vector<NodeID>> replace_vec_vec;

public:
    GraphPrinter(const vector<vector<NodeID>>& in_result, const vector<vector<NodeID>>& in_id_map, const vector<NodeID>& real_map, vector<EdgeID>& cellEdges, const int l): a_result(in_result), id_map(in_id_map), real_map(real_map), cell_edges(cellEdges), l(l), void_nodes(replace_vec){}
    GraphPrinter(const vector<NodeID>& void_nodes, vector<EdgeID>& cellEdges): void_nodes(void_nodes), cell_edges(cellEdges), id_map(replace_vec_vec), real_map(replace_vec), a_result(replace_vec_vec), l(0){}
    void write_void_result(mutex& w_lock, vector<vector<NodeID>>& res_cells_nodes, vector<vector<NodeID>>& res_cells_edges);
    void write_MLP_result(mutex& w_lock, vector<vector<NodeID>>& res_cells_nodes, vector<vector<NodeID>>& res_cells_edges, vector<vector<NodeID>>& res_void_cells);
    NodeID cuts_result_size(){return result_cuts.size();}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
