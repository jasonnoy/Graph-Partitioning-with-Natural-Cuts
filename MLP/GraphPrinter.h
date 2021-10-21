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

class GraphPrinter {
private:
    const int U;
    const vector<NodeID>& cell_nodes;
    const vector<vector<NodeID>>& cell_edges;
    const vector<vector<NodeID>>& id_map;
    const vector<vector<NodeID>>& a_result;
    vector<vector<NodeID>> result_nodes;
    vector<vector<NodeID>> result_edges;
    vector<vector<NodeID>> result_cuts;
    const string out_path;
    vector<NodeID> contract_to;

    void fill_contracts();
    void filter_edges();
    void MLP_result();
    void phantom_result();
    void contract_tiny_cells();
    void contract_iso_cells();

public:
    GraphPrinter(const vector<vector<NodeID>>& in_result, const vector<vector<NodeID>>& in_id_map, const vector<NodeID>& cellNodes, const vector<vector<NodeID>>& cellEdges, const string& o_path, const int u):
        a_result(in_result), id_map(in_id_map), cell_nodes(cellNodes), cell_edges(cellEdges), out_path(o_path), U(u){}
    void write_MLP_result(const string layer, vector<unsigned int>& real_map, bool isPhantom);
    unsigned int nodes_result_size(){return result_nodes.size();}
    unsigned int cuts_result_size(){return result_cuts.size();}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
