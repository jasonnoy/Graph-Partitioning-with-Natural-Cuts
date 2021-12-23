//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H

#include "../PUNCH/Assemble/A_Graph.h"

class Assembly {
private:
    int FI = 16;
    int M = 1;
    bool COMBINE = true;
    bool PHANTOM;
    vector<vector<NodeID>>& anodes;
    vector<vector<NodeID>>& aedges;

    vector<vector<NodeID>> result_nodes;
    vector<vector<NodeID>> id_map;
    A_Graph a_graph;


    void read_a_graph();
    void multistart_and_combination();
public:
    const int U;

    Assembly(int u, vector<vector<NodeID>>& a_nodes, vector<vector<NodeID>>& a_edges, const string oPath, bool phantom):
        U(u), anodes(a_nodes), aedges(a_edges), PHANTOM(phantom){};
    Assembly(int u, int fi, int m, bool combine, vector<vector<NodeID>>& a_nodes, vector<vector<NodeID>>& a_edges, bool phantom):
    U(u), FI(fi), M(m), COMBINE(combine), anodes(a_nodes), aedges(a_edges), PHANTOM(phantom){};
    void runAssembly();
    vector<vector<NodeID>>& get_result_nodes(){return result_nodes;}
    vector<vector<NodeID>>& get_id_map(){return id_map;}
};

void Assembly::read_a_graph(){
    cout<<"read in assemble graph...\n";
    a_graph.read_graph_n_idmap( id_map, anodes, aedges );
    printf("Done! Assemble graph has:\n%lu nodes and %lu edges\n", a_graph.get_node_list().size(), a_graph.get_edge_list().size());
}

void Assembly::multistart_and_combination(){
    cout<<"multi-start and combination (it may take a long time)...\n";
    a_graph.multistart_and_combination( result_nodes, U );
    cout<<"Done. Assemble result size: "<<result_nodes.size()<<endl;
}

void Assembly::runAssembly() {
    time_t start, mid, end;
    time(&start);
    a_graph.FI = this->FI;
    a_graph.M = this->M;
    a_graph.use_combine = this->COMBINE;
    read_a_graph();
    time(&mid);
    cout<<"assembly read graph time: "<<mid-start<<"s\n";
    multistart_and_combination();
    cout<<"Assembly phase done\n";

    time(&end);

    cout<<"Assembly run time: "<<end-start<<"s\n";
}

#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H
