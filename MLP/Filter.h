//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H

#include "../PUNCH/Filter/G_Graph.h"
#include "../Common/common.h"
#include <ctime>
#include <stdlib.h>

using namespace std;

class Filter {
private:
    G_Graph gGraph;
    const int U;
    const int Uf;
    const int C;
    int thread_cap;
    int F = 10;
    const vector<NodeID>& nodes;
    const vector<vector<NodeID>>& edges;
    vector<vector<NodeID>>& anodes;
    vector<vector<NodeID>>& aedges;
    vector<NodeID> real_map;

    void read_in_graph();
    void contract_tiny_cuts();
    void contract_natural_cuts();
    void convert_and_output();
public:
    Filter(int uf, int u, int c, const vector<NodeID>& in_nodes, const vector<vector<NodeID>>& in_edges, vector<vector<NodeID>>& a_nodes, vector<vector<NodeID>>& a_edges, int thread = 1):
    Uf(uf), U(u), C(c), nodes(in_nodes), edges(in_edges), anodes(a_nodes), aedges(a_edges), thread_cap(thread){
        gGraph.thread_cap = thread;
    };
    Filter(int uf, int u, int c, int f, const vector<NodeID>& in_nodes, const vector<vector<NodeID>>& in_edges, vector<vector<NodeID>>& a_nodes, vector<vector<NodeID>>& a_edges, int thread = 1):
            Uf(uf), U(u), C(c), F(f), nodes(in_nodes), edges(in_edges), anodes(a_nodes), aedges(a_edges), thread_cap(thread){
    };
    ~Filter() = default;
    void runFilter();
    int getF(){return F;}
    void setF(int f){F = f;}
    vector<vector<NodeID>>& get_anodes(){return anodes;}
    vector<vector<NodeID>>& get_aedges(){return aedges;}
    vector<NodeID>& get_real_map(){return real_map;}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H
