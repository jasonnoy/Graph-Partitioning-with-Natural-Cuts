//
// Created by 骏辉 on 2021/10/14.
//

#include "GraphPrinter.h"

void GraphPrinter::write_MLP_result(const string layer) {
    MLP_result();
    string out_node_path = out_path + "layer" + layer + "_nodes.txt";
    string out_edge_path = out_path + "layer" + layer + "_edges.txt";
    ofstream outfile;
    outfile.open(out_node_path, ios::app);
    if (!outfile.is_open()) {
        cout<<"Graph printer open file failed!\n";
        exit(1);
    }
    cout<<"Printing nodes of layer "<<layer<<endl;
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++) {
        outfile<<cell_iter->size()<<" ";
        for (auto nid_i = cell_iter->begin(); nid_i != cell_iter->end(); nid_i++) {
            outfile<<*nid_i<<" ";
        }
        outfile<<"\n";
    }
    outfile.close();
    outfile.clear(ios::goodbit);
    cout<<"Done\n";

    outfile.open(out_edge_path, ios::app);
    cout<<"Printing edges of layer "<<layer<<endl;
    for (auto edge_iter = result_edges.begin(); edge_iter != result_edges.end(); edge_iter++) {
        outfile<<edge_iter->at(0)<<" "<<edge_iter->at(1)<<endl;
    }
    outfile.close();
    cout<<"Done\n";
}

void GraphPrinter::MLP_result() {
    fill_contracts();

    result_nodes.resize(a_result.size());
    unsigned int index = 0;
    for (auto cit = a_result.begin(); cit!=a_result.end(); cit++, index++) {
        auto nit = cit->begin();
        result_nodes[index].reserve( 10 * cit->size() );
        for(; nit != cit->end(); nit++){
            for (auto map_iter : id_map[*nit]) {
                result_nodes[index].push_back(map_iter);
            }
        }
    }

    filter_edges();
}

void GraphPrinter::filter_edges() {
    bool* edge_map = new bool[cell_nodes.size()]();
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++) {
        for (auto nit = cell_iter->begin(); nit != cell_iter->end(); nit++) {
            edge_map[*nit] = 1;
        }
    }
    result_edges.reserve(cell_edges.size());
    for (int i = 0; i < cell_edges.size(); i++) {
        unsigned int sid = cell_edges[i][0];
        unsigned int tid = cell_edges[i][1];
        if (edge_map[sid] && edge_map[tid]) {
            vector<unsigned int> edge = {sid, tid};
            result_edges.push_back(edge);
        }
    }
}

void GraphPrinter::fill_contracts() {
    contract_to.resize(cell_nodes.size());
    for (int i = 0; i < result_nodes.size(); i++) {
        NodeID to_id = result_nodes[i][0];
        for (int j = 1; j < result_nodes[i].size(); j++) {
            contract_to[result_nodes[i][j]] = to_id;
        }
    }
}