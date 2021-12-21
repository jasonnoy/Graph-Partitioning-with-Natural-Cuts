//
// Created by 骏辉 on 2021/10/14.
//

#include "GraphPrinter.h"

void GraphPrinter::write_MLP_result(mutex& w_lock, vector<vector<NodeID>>& res_cells_nodes, vector<vector<NodeID>>& res_cells_edges, vector<vector<NodeID>>& res_void_cells) {
//    if (isPhantom) {
//        phantom_result();
//    } else {
//        MLP_result();
//    }
//    MLP_result();
    // convert relative vid to real nid
//    for (int i = 0; i < cell_void_nodes.size(); i++) {
//        cell_void_nodes[i] = real_map[cell_void_nodes[i]];
//    }

//    string out_node_path = out_path + "layer" + layer + "_nodes.txt";
//    string out_edge_path = out_path + "layer" + layer + "_edges.txt";
//    string out_cut_path = out_path + "layer" + layer + "_cuts.txt";
//    ofstream outfile;
//    outfile.open(out_node_path, ios::app);
//    if (!outfile.is_open()) {
//        cout<<"Graph printer open file failed!\n";
//        exit(1);
//    }
    cout<<"Printing nodes of layer "<<l<<endl;

    unordered_map<NodeID, int> node_cell;
//    NodeSize index = 0;
//    for (NodeSize i = 0; i < result_nodes.size(); i++, index++) {
//        for (NodeID node_iter : result_nodes[i]) {
//            node_cell[node_iter] = index;
//        }
//    }

    //    fill_contracts();
    size_t contracted_cell_count = 0;
//    result_nodes.resize(a_result.size());
    vector<vector<NodeID>> result_cells_nodes(a_result.size());
    NodeID index = 0;
    for (auto cell : a_result) {
        for (NodeID contain_id : cell) {
            for (NodeID nid: id_map[contain_id]) {
                NodeID rid = real_map[nid];
                result_cells_nodes[index].emplace_back(rid);
                node_cell[rid] = index;
            }
        }
        index++;
//        if (!contract_tiny || res_cell.size() > U/10 || res_cell.size() > 1000){
//            unique_lock<mutex> node_lock(n_lock);
//            res_cells_nodes.emplace_back(res_cell);
//            node_lock.unlock();
//            for (NodeID rid : res_cell) {
//                node_cell[rid] = index;
//            }
//
//            index++;
//            continue;
//        }
//        unique_lock<mutex> void_lock(v_lock);
//        res_void_cells.emplace_back(res_cell);
//        void_lock.unlock();
//        contracted_cell_count++;
    }
    const NodeSize valid_cell_num = a_result.size() - contracted_cell_count;
    cout<<"contracted "<<contracted_cell_count<<" tiny iso cells\n";
//    for (auto cit = a_result.begin(); cit!=a_result.end(); cit++, index++) {
//        auto nit = cit->begin();
//        result_nodes[index].reserve( 10 * cit->size() );
//        for(; nit != cit->end(); nit++){
//            for (NodeID contain_nid : id_map[*nit]) {
//                result_nodes[index].emplace_back(real_map[contain_nid]);
//            }
//        }
//    }
//
//    contract_tiny_cells();
//    if (contract_tiny)
//        contract_iso_cells();
//
//    unordered_map<NodeID, int> node_cell;
//    index = 0;
//    for (NodeSize i = 0; i < result_nodes.size(); i++, index++) {
//        for (NodeID node_iter : result_nodes[i]) {
//            node_cell[node_iter] = index;
//        }
//    }
//
//    result_cuts.reserve(cell_edges.size());
    vector<vector<NodeID>> result_cells_edges(valid_cell_num);
    for (EdgeID eid = 0; eid < cell_edges.size()/2; eid++) {
        NodeID sid = cell_edges[2*eid];
        NodeID tid = cell_edges[2*eid+1];
        if (node_cell[sid] == node_cell[tid]){
            result_cells_edges[node_cell[sid]].emplace_back(sid);
            result_cells_edges[node_cell[sid]].emplace_back(tid);
        }
    }
    unique_lock<mutex> write_lock(w_lock);
    for (auto cell_nodes : result_cells_nodes)
        res_cells_nodes.emplace_back(cell_nodes);
    for (auto cells_edges : result_cells_edges)
        res_cells_edges.emplace_back(cells_edges);
    write_lock.unlock();

    ofstream outfile("/data/jjh/mlp_test/Graph-Partitioning-with-Natural-Cuts/logs/20211221/temp.txt");
    outfile<<"nodes: ";
    for (NodeID nid : result_cells_nodes[0])
        outfile<<nid<<" ";
    outfile<<"\n edges: ";
    for (EdgeID eid = 0; eid < result_cells_edges[0].size()/2; eid++)
        outfile<<"s: "<<result_cells_edges[0][eid*2]<<" t: "<<result_cells_edges[0][eid*2+1]<<"; ";
    outfile<<"\n";

//
//    for (auto edge : cell_edges) {
//        // note: real ids
//        NodeID sid = edge[0];
//        NodeID tid = edge[1];
////        NodeID sid = cell_edges[2*i];
////        NodeID tid = cell_edges[2*i+1];
////        if(node_cell[sid] * node_cell[tid] < 0)
////            cout<<"node cell different\n";
//        if (node_cell[sid] == node_cell[tid]){
//            result_cells_edges[node_cell[sid]].emplace_back(sid);
//            result_cells_edges[node_cell[sid]].emplace_back(tid);
//            continue;
//        }
//        if (node_cell[sid] == -1 || node_cell[tid] == -1)
//            continue;
////        vector<NodeID> cut = {sid, tid};
////        result_cuts.emplace_back(cut);
//    }
//    filter_edges();

//    unique_lock<mutex> write_lock(w_lock);
//    for (auto new_cell_nodes : result_nodes)
//        res_cells_nodes.emplace_back(new_cell_nodes);
//    for (auto new_cell_edges : result_cells_edges)
//        res_cells_edges.emplace_back(new_cell_edges);
//    for (auto new_void_cells : void_cells)
//        res_void_cells.emplace_back(new_void_cells);
//    write_lock.unlock();
//    outfile.close();
//    outfile.clear(ios::goodbit);
    cout<<"Done\n";

//    outfile.open(out_cut_path, ios::app);
//    cout<<"Printing cuts of layer "<<layer<<" cut size: "<<result_cuts.size()<<endl;
//    for (auto cut_iter = result_cuts.begin(); cut_iter != result_cuts.end(); cut_iter++) {
//        outfile<<cut_iter->at(0)<<" "<<cut_iter->at(1)<<endl;
//    }
//    outfile.close();
//    outfile.clear(ios::goodbit);
//    cout<<"Done\n";

//    outfile.open(out_edge_path, ios::app);
//    cout<<"Printing edges of layer "<<layer<<endl;
//    int i = 0;
//    cout<<"Edge size: "<<result_edges.size()<<endl;
//    for (vector<NodeID> edge : result_edges) {
//        outfile<<edge[0]<<" "<<edge[1]<<endl;
//        cout<<i*100/result_edges.size()<<"\r";
//        i++;
//    }
//    cout<<"Done, ";
//    outfile.close();
//    outfile.clear(ios::goodbit);
//    cout<<"Done\n";
}

void GraphPrinter::phantom_result() {
//    fill_contracts();
//    cout<<"aresult size: "<<a_result.size()<<endl;
//    result_nodes.resize(a_result.size());
//    NodeID index = 0;
//    for (auto cit = a_result.begin(); cit!=a_result.end(); cit++, index++) {
//        result_nodes[index].reserve( cit->size() );
//        result_nodes[index].insert(result_nodes[index].end(), cit->begin(), cit->end());
//    }
//
//    result_cuts.reserve(cell_edges.size());
//    for (int i = 0; i < cell_edges.size(); i++) {
//        NodeID sid = cell_edges[i][0];
//        NodeID tid = cell_edges[i][1];
//        vector<NodeID> edge = {sid, tid};
//        result_cuts.push_back(edge);
//    }
}

void GraphPrinter::contract_tiny_cells() {
//    cout<<"contract tiny cells..\n";
//    int* num_cell = new int[cell_nodes.size()]();
//    int cell_id = 0;
//    vector<vector<NodeID>> node_edges;
//    node_edges.resize(cell_nodes.size());
//    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++, cell_id++) {
//        for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
//            num_cell[*nid] = cell_id;
//        }
//    }
//    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_id++) {
//        if (cell_iter->size() > U/10 || cell_iter->size() > 100){
//            cell_iter++;
//            continue;
//        }
//        int* cell_count = new int[cell_iter->size()]();
//        for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
//            for (NodeID tid : node_edges[*nid]) {
//                cell_count[num_cell[tid]]++;
//            }
////            cell_count[num_cell[node_edges[*nid]]]++;
//        }
//        int max_count = 0;
//        int max_cell = 0;
//        for (int i = 0; i < cell_iter->size(); i++) {
//            if (cell_count[i] > max_count){
//                max_count = cell_count[i];
//                max_cell = i;
//            }
//        }
//        for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
//            num_cell[*nid] = max_cell;
//        }
//        result_nodes[max_cell].insert(result_nodes[max_cell].end(), cell_iter->begin(), cell_iter->end());
//        cell_iter = result_nodes.erase(cell_iter);
//    }
    cout<<"Done\n";
}

void GraphPrinter::contract_iso_cells() {
//
//    int contracted_cell_count = 0;
//    auto cell_iter = result_nodes.begin();
//    while( cell_iter != result_nodes.end() ) {
//        if (cell_iter->size() > U/10 || cell_iter->size() > 1000) {
//            cell_iter++;
//            continue;
//        }
//        void_cells.emplace_back(*cell_iter);
//        cell_iter = result_nodes.erase(cell_iter);
////        cell_void_nodes.insert(cell_void_nodes.end(), cell_iter->begin(), cell_iter->end());
//        contracted_cell_count++;
//    }
//    cout<<"contracted "<<contracted_cell_count<<" tiny iso cells\n";
}

void GraphPrinter::MLP_result() {
////    fill_contracts();
//    result_nodes.resize(a_result.size());
//    NodeID index = 0;
//    for (auto cit = a_result.begin(); cit!=a_result.end(); cit++, index++) {
//        auto nit = cit->begin();
//        result_nodes[index].reserve( 10 * cit->size() );
//        for(; nit != cit->end(); nit++){
//            for (NodeID contain_nid : id_map[*nit]) {
//                result_nodes[index].emplace_back(real_map[contain_nid]);
//            }
//        }
//    }
//
////    contract_tiny_cells();
//    if (contract_tiny)
//        contract_iso_cells();
//
//    unordered_map<NodeID, int> node_cell;
//    index = 0;
//    for (NodeSize i = 0; i < result_nodes.size(); i++, index++) {
//        for (NodeID node_iter : result_nodes[i]) {
//            node_cell[node_iter] = index;
//        }
//    }
//
//    result_cuts.reserve(cell_edges.size());
//    result_cells_edges.resize(result_nodes.size());
//    for (auto edge : cell_edges) {
//        // note: real ids
//        NodeID sid = edge[0];
//        NodeID tid = edge[1];
////        NodeID sid = cell_edges[2*i];
////        NodeID tid = cell_edges[2*i+1];
////        if(node_cell[sid] * node_cell[tid] < 0)
////            cout<<"node cell different\n";
//        if (node_cell[sid] == node_cell[tid]){
//            result_cells_edges[node_cell[sid]].emplace_back(sid);
//            result_cells_edges[node_cell[sid]].emplace_back(tid);
//            continue;
//        }
//        if (node_cell[sid] == -1 || node_cell[tid] == -1)
//            continue;
//        vector<NodeID> cut = {sid, tid};
//        result_cuts.emplace_back(cut);
//    }
////    filter_edges();
}

void GraphPrinter::filter_edges() {
//    vector<bool> edge_map(cell_nodes.size(), false);
//    for (auto cell_iter = result_nodes.begin(); cell_iter != result_nodes.end(); cell_iter++) {
//        for (auto nit = cell_iter->begin(); nit != cell_iter->end(); nit++) {
//            edge_map[*nit] = 1;
//        }
//    }
//    result_cuts.reserve(cell_edges.size());
//    for (int i = 0; i < cell_edges.size(); i++) {
//        NodeID sid = cell_edges[i][0];
//        NodeID tid = cell_edges[i][1];
//        if (edge_map[sid] && edge_map[tid]) {
//            vector<NodeID> edge = {sid, tid};
//            result_cuts.push_back(edge);
//        }
//    }
}

//void GraphPrinter::fill_contracts() {
//    contract_to.resize(cell_nodes.size());
//    for (int i = 0; i < result_nodes.size(); i++) {
//        NodeID to_id = result_nodes[i][0];
//        for (int j = 1; j < result_nodes[i].size(); j++) {
//            contract_to[result_nodes[i][j]] = to_id;
//        }
//    }
//}