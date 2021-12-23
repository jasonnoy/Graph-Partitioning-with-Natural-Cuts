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
    vector<NodeID>& nodes;
    vector<EdgeID>& edges;
    vector<vector<NodeID>>& anodes;
    vector<vector<NodeID>>& aedges;
    vector<NodeID> real_map;

    void read_in_graph();
    void contract_tiny_cuts();
    void contract_natural_cuts();
    void convert_and_output();
public:
    Filter(int uf, int u, int c, vector<NodeID>& in_nodes, vector<EdgeID>& in_edges, vector<vector<NodeID>>& a_nodes, vector<vector<NodeID>>& a_edges, int thread = 1):
    Uf(uf), U(u), C(c), nodes(in_nodes), edges(in_edges), anodes(a_nodes), aedges(a_edges), thread_cap(thread){
        gGraph.thread_cap = thread;
        gGraph.DNCC = c;
    };
    Filter(int uf, int u, int c, int f, vector<NodeID>& in_nodes, vector<NodeID>& in_edges, vector<vector<NodeID>>& a_nodes, vector<vector<NodeID>>& a_edges, int thread = 1):
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


void Filter::read_in_graph(){
    //read in graph
    cout<<"Reading last layer data...\n";
    gGraph.read_graph(nodes, edges, real_map);
}


void Filter::contract_tiny_cuts(){

    //first pass: first ignored, then added behind for convenience

    //third pass: process 2-cuts classes elaborate
    //make a dfs tree on the graph
    cout<<"get DFS tree...\n";
//    vector<bool> final_edge_in_fi
    vector<bool> edge_in_fi( gGraph.get_edge_list().size(), true );
//    int thread_capacity = (thread_limit-thread_occupied)/thread_occupied;
    time_t start, end;
    time(&start);
    gGraph.dfs_tree( 0, edge_in_fi, 0);
    time(&end);
    cout<<"Time cost: "<<end-start<<"s\n";

    NodeID ten = 0;
    for( int i = 0; i < edge_in_fi.size(); i++ ){
        if( !edge_in_fi[i] )
            ten++;
    }
    printf("done! There are %zu edge (%.1f%%) in tree.\n", ten, ten*100.0/edge_in_fi.size());

    cout<<"find edge classes...\n";
    time(&start);
    vector< vector<EdgeID> > edge_equl_cls;
    gGraph.two_cuts_edge_class( edge_in_fi, edge_equl_cls ); //edge_equl_cls[0] is the class of 1-cut

    cout<<"Done. Contract two cuts...\n";
    //handle each class, cut gGraph to components and contract small ones
    gGraph.cnt_two_cuts( edge_equl_cls, Uf );
    printf("Done! Contract %u nodes (%.1f%%)\n", gGraph.get_del_node_num(),
           gGraph.get_del_node_num()*100.0/gGraph.get_node_list().size());
    time(&end);
    cout<<"Time cost: "<<end-start<<"s\n";

    /* we assume that 1-cut has nothing to do with 2-cut, so the first can be added
    /* after the third and second pass. Here we use the algorith same as dectecting
    /* 2-cuts to find all 1-cuts (bridges). During the above contraction process some
    /* of them are contained in the same contracted node, and they are thus ingored. */

    //edge_equl_cls[0] is the class of 1-cut
    cout<<"contract one cuts...\n";
    cout<<"size of 1-cut: "<<edge_equl_cls[0].size()<<endl;
    time(&start);
    gGraph.cnt_one_cuts( edge_equl_cls[0], Uf );
    printf("done! Contract %lu nodes (%.1f%%)\n", gGraph.get_del_node().size(),
           gGraph.get_del_node().size()*100.0/gGraph.get_node_list().size());
    time(&end);
    cout<<"Time cost: "<<end-start<<"s\n";

    cout<<"contract two-degree-node paths...\n";
    //second pass: contract 2-degree-node paths
    time(&start);
    gGraph.cnt_two_degree_path( Uf );
    printf("done! Contract %lu nodes (%.1f%%)\n", gGraph.get_del_node().size(),
           gGraph.get_del_node().size()*100.0/gGraph.get_node_list().size());
    time(&end);
    cout<<"Time cost: "<<end-start<<"s\n";

    return;
}

void Filter::contract_natural_cuts(){
    cout<<"thread_cap: "<<thread_cap<<endl;
    cout<<"find all natural cuts...\n";
    //vector<bool> natural_cuts( graph.get_edge_list().size(), false );
    bool * natural_cuts = NULL;
    natural_cuts = new bool[ gGraph.get_edge_list().size() ];
//    if( !natural_cuts ){ printf("ERROR bad alloc: natural_cuts!\n"); exit(0); }
    memset( natural_cuts, false, gGraph.get_edge_list().size() );
    time_t start, end;
    time(&start);
    gGraph.find_natural_cuts( natural_cuts, U );
    time(&end);
    cout<<"find natural cut time cost: "<<end-start<<"s\n";

    NodeID ten = 0;
    for( int i = 0; i < gGraph.get_edge_list().size(); i++ ){
        if( natural_cuts[i])
            ten++;
    }
    printf("done! There are %zu edges (%.1f%%) are natural cuts.\n",
           ten, ten*100.0/gGraph.get_edge_list().size());

    cout<<"contract natural cuts...\n";
    time(&start);
    gGraph.cnt_natural_cuts( natural_cuts );
    printf("done! Contract %lu nodes (%.1f%%)\n", gGraph.get_del_node().size(),
           gGraph.get_del_node().size()*100.0/gGraph.get_node_list().size());
    time(&end);
    cout<<"Contract natural cut time cost: "<<end-start<<"s\n"<<endl;

    delete[] natural_cuts;

    return;
}

void Filter::convert_and_output(){

    cout<<"Convert to assemble gGraph and output...\n";
    cout<<"aedges size: "<<aedges.size()<<endl;
    gGraph.convert_n_output( anodes, aedges );
    cout<<"Filter phase done!\n";

}

void Filter::runFilter() {
    time_t start, mid, end;
    time(&start);
    read_in_graph();
    time(&mid);
    cout<<"Filter read graph time cost: "<<mid-start<<"s\n";
    contract_tiny_cuts();
    time(&end);
    cout<<"contract tiny cuts time cost: "<<end-mid<<"s\n";
    contract_natural_cuts();
    time(&mid);
    cout<<"contract natural cuts time cost: "<<mid-end<<"s\n";
    convert_and_output();
    end = time(&end);
    cout<<"convert time cost: "<<end-mid<<"s\n";
    int time_cost = end - start;
    cout<<"filter run time: "<<time_cost<<"s.\n";
}
#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H
