//
// Created by 骏辉 on 2021/10/14.
//

#include "GraphPrinter.h"

void GraphPrinter::write_phantom_result() {
    phantom_result();
    string out_node_path = out_path + "layer-1_nodes.txt";
    string out_edge_path = out_path + "layer-1_edges.txt";
    string out_phantom_path = out_path + "phantom_nodes.txt";
    ofstream outfile;
    outfile.open(out_node_path);
    if (!outfile.is_open()) {
        cout<<"Graph printer open file failed!\n";
        exit(1);
    }
    cout<<"Printing nodes of phantom layer\n";
    outfile<<"0\n1\n";
    outfile<<result_nodes.size();
    for (NodeID nid = 0; nid < result_nodes.size(); nid++)
        outfile<<" "<<nid;
//    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++) {
//        for (auto nid_i = cell_iter->begin(); nid_i != cell_iter->end(); nid_i++) {
//            outfile<<" "<<*nid_i;
//        }
//    }
    outfile<<"\n";
    outfile.close();
    outfile.clear(ios::goodbit);

    outfile.open(out_edge_path);
    cout<<"Printing edges of phantom layer\n";
    outfile<<result_edges.size()<<"\n";
    for (auto edge_iter = result_edges.begin(); edge_iter != result_edges.end(); edge_iter++) {
        outfile<<edge_iter->at(0)<<" "<<edge_iter->at(1)<<endl;
    }
    outfile.close();
    outfile.clear(ios::goodbit);

    outfile.open(out_phantom_path);
    if (!outfile.is_open()) {
        cout<<"Graph printer open file failed!\n";
        exit(1);
    }
    cout<<"Printing phantom layer node map\n";
    outfile<<phantom_nodes.size()<<"\n";
    for (auto cell_iter:phantom_nodes){
        outfile<<cell_iter.size();
        for (NodeID nid:cell_iter){
            outfile<<" "<<nid;
        }
        outfile<<"\n";
    }
    cout<<"Done\n";
    outfile.close();
}

void GraphPrinter::write_MLP_result(const string layer, vector<unsigned int>& real_map) {
    MLP_result();

    // convert relative vid to real nid
    for (int i = 0; i < cell_void_nodes.size(); i++) {
        cell_void_nodes[i] = real_map[cell_void_nodes[i]];
    }

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
    result_nodes.resize(a_result.size());
    unsigned int index = 0;
    unsigned int* node_map = new unsigned int[cell_nodes.size()]();
    phantom_nodes.resize(a_result.size());
    for (auto cit = a_result.begin(); cit!=a_result.end(); cit++, index++) {
        result_nodes[index].push_back(index);
        for (NodeID nid : *cit) {
            node_map[nid] = index;
            for (NodeID c_nid : id_map[nid])
                node_map[c_nid] = index;
            phantom_nodes[index].insert(phantom_nodes[index].end(), id_map[nid].begin(), id_map[nid].end());
        }
    }

    result_edges.reserve(cell_edges.size());
    for (int i = 0; i < cell_edges.size(); i++) {
        unsigned int sid = cell_edges[i][0];
        unsigned int tid = cell_edges[i][1];
        unsigned int phantom_sid = node_map[sid];
        unsigned int phantom_tid = node_map[tid];
        if (phantom_sid != phantom_tid) {
            vector<unsigned int> edge = {phantom_sid, phantom_tid};
            result_edges.push_back(edge);
        }
    }
    delete []node_map;
}

void GraphPrinter::contract_tiny_cells() {
    cout<<"contract tiny cells..\n";
    int* num_cell = new int[cell_nodes.size()]();
    int cell_id = 0;
    vector<vector<unsigned int>> node_edges;
    node_edges.resize(cell_nodes.size());
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++, cell_id++) {
        for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
            num_cell[*nid] = cell_id;
        }
    }
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_id++) {
        if (cell_iter->size() > U/10 || cell_iter->size() > 100){
            cell_iter++;
            continue;
        }
        int* cell_count = new int[cell_iter->size()]();
        for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
            for (unsigned int tid : node_edges[*nid]) {
                cell_count[num_cell[tid]]++;
            }
//            cell_count[num_cell[node_edges[*nid]]]++;
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
            num_cell[*nid] = max_cell;
        }
        result_nodes[max_cell].insert(result_nodes[max_cell].end(), cell_iter->begin(), cell_iter->end());
        cell_iter = result_nodes.erase(cell_iter);
    }
    delete[] num_cell;
    cout<<"Done\n";
}

void GraphPrinter::contract_iso_cells() {

    int contracted_cell_count = 0;
    auto cell_iter = result_nodes.begin();
    while( cell_iter != result_nodes.end() ) {
        if (cell_iter->size() > U/10 || cell_iter->size() > 100) {
            cell_iter++;
            continue;
        }
        for (auto node_iter = cell_iter->begin(); node_iter != cell_iter->end(); node_iter++) {
            if (*node_iter >= cell_nodes.size())
                cout<<"oversize vid: "<<*node_iter<<endl;
            cell_void_nodes.push_back(*node_iter);
        }
        cell_iter = result_nodes.erase(cell_iter);
//        cell_void_nodes.insert(cell_void_nodes.end(), cell_iter->begin(), cell_iter->end());
        contracted_cell_count++;
    }
    cout<<"contracted "<<contracted_cell_count<<" tiny iso cells\n";
}

void GraphPrinter::MLP_result() {
    fill_contracts();
    result_nodes.resize(a_result.size());
    unsigned int index = 0;
    for (auto cit = a_result.begin(); cit!=a_result.end(); cit++, index++) {
        auto nit = cit->begin();
        result_nodes[index].reserve( 10 * cit->size() );
        for(; nit != cit->end(); nit++){
            for (NodeID contain_nid : id_map[*nit]) {
                result_nodes[index].push_back(contain_nid);
            }
        }
    }

//    contract_tiny_cells();
    if (contract_tiny)
        contract_iso_cells();

    int * node_cell = new int[cell_nodes.size()]();
    index = 0;
    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++, index++) {
        for (auto node_iter = cell_iter->begin(); node_iter != cell_iter->end(); node_iter++) {
            node_cell[*node_iter] = index;
        }
    }
    for (unsigned int void_id : cell_void_nodes) {
        if (void_id >= cell_nodes.size()) {
            cout<<"outsize void_id: "<<void_id<<endl;
        }
        node_cell[void_id] = -1;
    }
    result_cuts.reserve(cell_edges.size());
    result_edges.reserve(cell_edges.size());
    for (int i = 0; i < cell_edges.size(); i++) {
        unsigned int sid = cell_edges[i][0];
        unsigned int tid = cell_edges[i][1];
//        if(node_cell[sid] * node_cell[tid] < 0)
//            cout<<"node cell different\n";
        if (node_cell[sid] == node_cell[tid]){
            vector<unsigned int> edge = {sid, tid};
            result_edges.push_back(edge);
            continue;
        }
        if (node_cell[sid] == -1 || node_cell[tid] == -1)
            continue;
        vector<unsigned int> cut = {sid, tid};
        result_cuts.push_back(cut);
    }
//    filter_edges();
delete[] node_cell;
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
    delete[] edge_map;
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