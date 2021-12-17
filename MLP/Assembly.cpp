//
// Created by 骏辉 on 2021/10/12.
//

#include "Assembly.h"

void Assembly::read_a_graph(){
    cout<<"read in assemble graph...\n";
    a_graph.read_graph_n_idmap( id_map, anodes, aedges );
    printf("Done! Assemble graph has:\n%lu nodes and %lu edges\n", a_graph.get_node_list().size(), a_graph.get_edge_list().size());
}

void Assembly::multistart_and_combination(){
    cout<<"multi-start and combination (it may take a long time)...\n";
    a_graph.multistart_and_combination( result_nodes, result_edges, U );
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
    // free mem
    a_graph.~A_Graph();
    cout<<"Assembly phase done\n";

    time(&end);

    cout<<"Assembly run time: "<<end-start<<"s\n";
}