//
// Created by 骏辉 on 2021/10/12.
//

#include "Filter.h"

void Filter::read_in_graph(){
    //read in graph
    cout<<"Reading input file...\n";
    gGraph.read_graph(nodes, edges);
    cout<<"Done!\n";
}


void Filter::contract_tiny_cuts(){

    //first pass: first ignored, then added behind for convenience

    //third pass: process 2-cuts classes elaborate
    //make a dfs tree on the graph
    cout<<"get DFS tree...\n";
    vector<bool> edge_in_fi( gGraph.get_edge_list().size(), true );
    gGraph.dfs_tree( 0, edge_in_fi, 0);

    size_t ten = 0;
    for( int i = 0; i < edge_in_fi.size(); i++ ){
        if( !edge_in_fi[i] )
            ten++;
    }
    printf("done!\nthere are %zu edge (%.1f%%) in tree.\n", ten, ten*100.0/edge_in_fi.size());

    cout<<"find edge classes...\n";
    vector< vector<EdgeID> > edge_equl_cls;
    gGraph.two_cuts_edge_class( edge_in_fi, edge_equl_cls ); //edge_equl_cls[0] is the class of 1-cut
    cout<<"Done!\n";

    cout<<"contract two cuts...\n";
    //handle each class, cut gGraph to components and contract small ones
    gGraph.cnt_two_cuts( edge_equl_cls, U );
    printf("done!\ncontract %lu nodes (%.1f%%)\n", gGraph.get_del_node().size(),
           gGraph.get_del_node().size()*100.0/gGraph.get_node_list().size());

    /* we assume that 1-cut has nothing to do with 2-cut, so the first can be added
    /* after the third and second pass. Here we use the algorith same as dectecting
    /* 2-cuts to find all 1-cuts (bridges). During the above contraction process some
    /* of them are contained in the same contracted node, and they are thus ingored. */

    //edge_equl_cls[0] is the class of 1-cut
    cout<<"contract one cuts...";
    gGraph.cnt_one_cuts( edge_equl_cls[0], U );
    printf("done!\ncontract %lu nodes (%.1f%%)\n", gGraph.get_del_node().size(),
           gGraph.get_del_node().size()*100.0/gGraph.get_node_list().size());

    cout<<"contract two-degree-node paths...\n";
    //second pass: contract 2-degree-node paths
    gGraph.cnt_two_degree_path( U );
    printf("done!\ncontract %lu nodes (%.1f%%)\n", gGraph.get_del_node().size(),
           gGraph.get_del_node().size()*100.0/gGraph.get_node_list().size());

    return;
}

void Filter::contract_natural_cuts(){

    cout<<"find all natural cuts...\n";
    //vector<bool> natural_cuts( graph.get_edge_list().size(), false );
    bool * natural_cuts = NULL;
    natural_cuts = new bool[ gGraph.get_edge_list().size() ];
//    if( !natural_cuts ){ printf("ERROR bad alloc: natural_cuts!\n"); exit(0); }
    memset( natural_cuts, false, gGraph.get_edge_list().size() );
    gGraph.find_natural_cuts( natural_cuts, U );

    size_t ten = 0;
    for( int i = 0; i < gGraph.get_edge_list().size(); i++ ){
        if( natural_cuts[i])
            ten++;
    }
    printf("done!\nthere are %zu edges (%.1f%%) are natural cuts.\n",
           ten, ten*100.0/gGraph.get_edge_list().size());

    cout<<"contract natural cuts...\n";
    gGraph.cnt_natural_cuts( natural_cuts );
    printf("done!\ncontract %lu nodes (%.1f%%)\n", gGraph.get_del_node().size(),
           gGraph.get_del_node().size()*100.0/gGraph.get_node_list().size());

    delete[] natural_cuts;

    return;
}

void Filter::convert_and_output(){

    cout<<"convert to assemble gGraph and output...\n";
    gGraph.convert_n_output( anodes, aedges );
    cout<<"done!\n";

}

void Filter::runFilter() {
    clock_t start, end;
    start = clock();
    read_in_graph();
    contract_tiny_cuts();
    contract_natural_cuts();
    convert_and_output();
    end = clock();
    int time = (end - start) / CLOCKS_PER_SEC;
    cout<<"Filter run time: "<<time<<"s.\n";
}