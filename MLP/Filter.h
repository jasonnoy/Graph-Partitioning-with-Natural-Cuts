//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H

#include "../PUNCH/Filter/G_Graph.h"
#include <ctime>
#include <stdlib.h>

using namespace std;

class Filter {
private:
    G_Graph gGraph;
    const int U;
    const int C;
    const int F;
    const vector<unsigned int>& nodes;
    const vector<vector<unsigned int>>& edges;
    vector<vector<unsigned int>>& anodes;
    vector<vector<unsigned int>>& aedges;
    vector<unsigned int> real_map;

    void read_in_graph();
    void contract_tiny_cuts();
    void contract_natural_cuts();
    void convert_and_output();
public:
    Filter(int u, int c, const vector<unsigned int>& in_nodes, const vector<vector<unsigned int>>& in_edges, vector<vector<unsigned int>>& a_nodes, vector<vector<unsigned int>>& a_edges):
    U(u), C(c), nodes(in_nodes), edges(in_edges), anodes(a_nodes), aedges(a_edges){
        gGraph = new G_Graph(c, 10);
    };
    Filter(int u, int c, int f, const vector<unsigned int>& in_nodes, const vector<vector<unsigned int>>& in_edges, vector<vector<unsigned int>>& a_nodes, vector<vector<unsigned int>>& a_edges):
            U(u), C(c), F(f), nodes(in_nodes), edges(in_edges), anodes(a_nodes), aedges(a_edges){
        gGraph = new G_Graph(c, f);
    };
    ~Filter() = default;
    void runFilter();
    int getF(){return F;}
    void setF(int f){F = f;}
    vector<vector<unsigned int>>& get_anodes(){return anodes;}
    vector<vector<unsigned int>>& get_aedges(){return aedges;}
    vector<unsigned int>& get_real_map(){return real_map;}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H
