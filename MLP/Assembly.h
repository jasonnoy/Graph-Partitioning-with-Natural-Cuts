//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H

#include "../Assemble/A_Graph.h"

class Assembly {
private:
    int FI = 16;
    int M = 1;
    bool COMBINE = false;
    bool PHANTOM;
    vector<vector<NodeID>>& anodes;
    vector<vector<NodeID>>& aedges;

    vector<vector<NodeID>> result;
    vector<vector<NodeID>> id_map;
    R_Graph real_graph;
    A_Graph a_graph;


    void read_a_graph();
    void multistart_and_combination();
    void write_result();
public:
    const int U;
    const string outPath;

    Assembly(int u, vector<vector<NodeID>>& a_nodes, vector<vector<NodeID>>& a_edges, const string oPath, bool phantom):
        U(u), anodes(a_nodes), aedges(a_edges), outPath(oPath), PHANTOM(phantom){};
    Assembly(int u, int fi, int m, bool combine, vector<vector<NodeID>>& a_nodes, vector<vector<NodeID>>& a_edges, const string oPath, bool phantom):
    U(u), FI(fi), M(m), COMBINE(combine), anodes(a_nodes), aedges(a_edges), outPath(oPath), PHANTOM(phantom){};
    void runAssembly();
    vector<vector<NodeID>>& get_result(){return result;}
    vector<vector<NodeID>>& get_id_map(){return id_map;}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H
