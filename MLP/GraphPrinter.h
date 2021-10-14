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
    const vector<NodeID>& cell_nodes;
    const vector<vector<NodeID>>& cell_edges;
    const vector<vector<NodeID>>& id_map;
    const vector<vector<NodeID>>& a_result;
    vector<vector<NodeID>> result_nodes;
    vector<vector<NodeID>> result_edges;
    const string out_path;
    bool isPhantom;
    vector<NodeID> contract_to;

    void fill_contracts();
    void filter_edges();
    void MLP_result();

public:
    GraphPrinter(const vector<vector<NodeID>>& in_result, const vector<vector<NodeID>>& in_id_map, const vector<NodeID>& cellNodes, const vector<vector<NodeID>>& cellEdges, const string& o_path, bool phantom):
        a_result(in_result), id_map(in_id_map), cell_nodes(cellNodes), cell_edges(cellEdges), out_path(o_path), isPhantom(phantom){}
    void write_MLP_result(const string layer);
    unsigned int nodes_result_size(){return result_nodes.size();}
    unsigned int edges_result_size(){return result_edges.size();}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
