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

using namespace std;

#include "../Common/common.h"
#include <unordered_map>

class GraphPrinter {
private:
    const int U;
    const int l;
    const bool contract_tiny;
    vector<vector<NodeID>>& cell_edges;
//    vector<NodeID> cell_nodes;
    const vector<vector<NodeID>>& id_map;
    const vector<NodeID>& real_map;
    const vector<vector<NodeID>>& a_result;
    vector<vector<NodeID>> phantom_nodes;
    vector<vector<NodeID>> result_nodes;
    vector<vector<NodeID>> result_cells_edges;
    vector<vector<NodeID>> result_cuts;
    vector<vector<NodeID>> void_cells;
//    const string out_path;
//    vector<NodeID> contract_to;
//    vector<NodeID> cell_void_nodes;

    void fill_contracts();
    void filter_edges();
    void MLP_result();
    void phantom_result();
    void contract_tiny_cells();
    void contract_iso_cells();

public:
    GraphPrinter(const vector<vector<NodeID>>& in_result, const vector<vector<NodeID>>& in_id_map, const vector<NodeID>& real_map, vector<vector<EdgeID>>& cellEdges,  const int u, const int l, const bool contract): a_result(in_result), id_map(in_id_map), real_map(real_map), cell_edges(cellEdges), U(u), l(l), contract_tiny(contract){}
    void write_MLP_result(vector<vector<NodeID>>& cells_nodes, vector<vector<EdgeID>>& cells_edges, vector<vector<NodeID>>& res_void_cells, mutex& w_lock);
//    NodeID nodes_result_size(){return result_nodes.size();}
    NodeID cuts_result_size(){return result_cuts.size();}
//    vector<NodeID>& get_cell_void_nodes(){return cell_void_nodes;}
    vector<vector<NodeID>>& get_void_cells(){return void_cells;}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
