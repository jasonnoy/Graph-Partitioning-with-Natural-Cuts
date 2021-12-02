//
// Created by 骏辉 on 2021/10/14.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H

#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

#include "../Common/common.h"
#include <map>

class GraphPrinter {
private:
    const int U;
    const bool contract_tiny;
    const vector<NodeID>& cell_nodes;
    const vector<vector<NodeID>>& cell_edges;
    const vector<vector<NodeID>>& id_map;
    const vector<unsigned int>& real_map;
    const vector<vector<NodeID>>& a_result;
    vector<vector<NodeID>> phantom_nodes;
    vector<vector<NodeID>> result_nodes;
    vector<vector<NodeID>> result_edges;
    vector<vector<NodeID>> result_cuts;
    vector<vector<NodeID>> void_cells;
    const string out_path;
    vector<NodeID> contract_to;
    vector<NodeID> cell_void_nodes;

    void fill_contracts();
    void filter_edges();
    void MLP_result();
    void phantom_result();
    void contract_tiny_cells();
    void contract_iso_cells();

public:
    GraphPrinter(const vector<vector<NodeID>>& in_result, const vector<vector<NodeID>>& in_id_map, const vector<NodeID>& real_map, const vector<NodeID>& cellNodes, const vector<vector<NodeID>>& cellEdges, const string o_path, const int u, const bool contract): a_result(in_result), id_map(in_id_map), real_map(real_map), cell_nodes(cellNodes), cell_edges(cellEdges), out_path(o_path), U(u), contract_tiny(contract){}
    void write_MLP_result(const string layer, bool isPhantom);
    NodeID nodes_result_size(){return result_nodes.size();}
    NodeID cuts_result_size(){return result_cuts.size();}
    vector<NodeID>& get_cell_void_nodes(){return cell_void_nodes;}
    vector<vector<NodeID>>& get_void_cells(){return void_cells;}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
