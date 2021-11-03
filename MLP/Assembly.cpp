//
// Created by 骏辉 on 2021/10/12.
//
#define cout /##/
#define printf /##/

#include "Assembly.h"

void Assembly::read_a_graph(){
    cout<<"read in assemble graph...\n";
    a_graph.read_graph_n_idmap( id_map, anodes, aedges );
    printf("Done! Assemble graph has:\n%lu nodes and %lu edges\n", a_graph.get_node_list().size(), a_graph.get_edge_list().size());
}

void Assembly::multistart_and_combination(){
    cout<<"multi-start and combination (it may take a long time)...\n";
    a_graph.multistart_and_combination( result, U );
    cout<<"Done. Assemble result size: "<<result.size()<<endl;
}

void Assembly::write_result(){
    cout<<"write result into target directory...\n";
//    EdgeWeight weight = real_graph.write_result( result, id_map, nodePath, graphPath, outPath, PHANTOM ); // for test only
//    printf("Done! Total weight of the cut edges is: %u\n", weight);
}

void Assembly::runAssembly() {
    clock_t start, end;
    start = clock();
    a_graph.FI = this->FI;
    a_graph.M = this->M;
    a_graph.use_combine = this->COMBINE;
    read_a_graph();
    multistart_and_combination();
    cout<<"Assembly phase done\n";
//    write_result();
    end = clock();
    int time = (end - start) / CLOCKS_PER_SEC;
    cout<<"Assembly run time: "<<time<<"s\n";
}