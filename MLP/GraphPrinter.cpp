//
// Created by 骏辉 on 2021/10/14.
//

#include "GraphPrinter.h"

void GraphPrinter::write_MLP_result(const string layer, vector<unsigned int>& real_map, bool isPhantom) {
//    if (isPhantom) {
//        phantom_result();
//    } else {
//        MLP_result();
//    }
    MLP_result();

    string out_node_path = out_path + "layer" + layer + "_nodes.txt";
    string out_edge_path = out_path + "layer" + layer + "_edges.txt";
    string out_cut_path = out_path + "layer" + layer + "_cuts.txt";
    ofstream outfile;
    outfile.open(out_node_path, ios::app);
    if (!outfile.is_open()) {
        cout<<"Graph printer open file failed!\n";
        exit(1);
    }
    cout<<"Printing nodes of layer "<<layer<<endl;
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++) {
        outfile<<cell_iter->size();
        for (auto nid_i = cell_iter->begin(); nid_i != cell_iter->end(); nid_i++) {
            outfile<<" "<<real_map[*nid_i];
        }
        outfile<<"\n";
    }
    outfile.close();
    outfile.clear(ios::goodbit);
    cout<<"Done\n";

    outfile.open(out_cut_path, ios::app);
    cout<<"Printing cuts of layer "<<layer<<endl;
    for (auto cut_iter = result_cuts.begin(); cut_iter != result_cuts.end(); cut_iter++) {
        outfile<<cut_iter->at(0)<<" "<<cut_iter->at(1)<<endl;
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

void GraphPrinter::phantom_result() {
    fill_contracts();
    cout<<"aresult size: "<<a_result.size()<<endl;
    result_nodes.resize(a_result.size());
    unsigned int index = 0;
    for (auto cit = a_result.begin(); cit!=a_result.end(); cit++, index++) {
        result_nodes[index].reserve( cit->size() );
        result_nodes[index].insert(result_nodes[index].end(), cit->begin(), cit->end());
    }

    result_cuts.reserve(cell_edges.size());
    for (int i = 0; i < cell_edges.size(); i++) {
        unsigned int sid = cell_edges[i][0];
        unsigned int tid = cell_edges[i][1];
        vector<unsigned int> edge = {sid, tid};
        result_cuts.push_back(edge);
    }
}

void GraphPrinter::contract_tiny_result_nodes() {
    unsigned int* num_cell = new unsigned int[cell_nodes.size()]();
    int cell_id = 0;
    vector<vector<unsigned int>> node_edges;
    node_edges.resize(cell_nodes.size());
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++, cell_id++) {
        for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
            num_cell[nid] = cell_id;
        }
    }
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++, cell_id++) {
        if (cell_iter->size() > U/10 || cell_iter->size() > 100)
            continue;
        int* cell_count = new int[cell_iter->size()]();
        for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
            cell_count[num_cell[node_edges[*nid]]]++;
        }
        int max_count = 0;
        int max_cell = 0;
        for (int i = 0; i < cell_iter->size(); i++) {
            if (cell_count[i] > max_count){
                max_count = cell_count[i];
                max_cell = i;
            }
        }
        for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
            num_cell[nid] = max_cell;
        }
        result_nodes[max_cell].insert(result_nodes[max_cell].end(), cell_iter->begin(), cell_iter->end());
        cell_iter = result_nodes.erase(cell_iter);
    }
}
void GraphPrinter::MLP_result() {
    fill_contracts();
    cout<<"aresult size: "<<a_result.size()<<endl;
    result_nodes.resize(a_result.size());
    int * node_cell = new int[cell_nodes.size()]();
    unsigned int index = 0;
    for (auto cit = a_result.begin(); cit!=a_result.end(); cit++, index++) {
        auto nit = cit->begin();
        result_nodes[index].reserve( 10 * cit->size() );
        for(; nit != cit->end(); nit++){
            for (NodeID contain_nid : id_map[*nit]) {
                node_cell[contain_nid] = index;
                result_nodes[index].push_back(contain_nid);
            }
        }
    }

    result_cuts.reserve(cell_edges.size());
    result_edges.reserve(cell_edges.size());
    for (int i = 0; i < cell_edges.size(); i++) {
        unsigned int sid = cell_edges[i][0];
        unsigned int tid = cell_edges[i][1];
        if (node_cell[sid] == node_cell[tid]){
            vector<unsigned int> edge = {sid, tid};
            result_edges.push_back(edge);
            continue;
        }
        vector<unsigned int> cut = {sid, tid};
        result_cuts.push_back(cut);
    }
//    filter_edges();
}

void GraphPrinter::filter_edges() {
    bool* edge_map = new bool[cell_nodes.size()]();
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++) {
        for (auto nit = cell_iter->begin(); nit != cell_iter->end(); nit++) {
            edge_map[*nit] = 1;
        }
    }
    result_cuts.reserve(cell_edges.size());
    for (int i = 0; i < cell_edges.size(); i++) {
        unsigned int sid = cell_edges[i][0];
        unsigned int tid = cell_edges[i][1];
        if (edge_map[sid] && edge_map[tid]) {
            vector<unsigned int> edge = {sid, tid};
            result_cuts.push_back(edge);
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