//
// Created by 骏辉 on 2021/10/14.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H

#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#include "../Common/common.h"

class GraphPrinter {
private:
    const int l;
    vector<NodeID>& cell_edges;
    const vector<NodeID>& void_nodes;
//    vector<NodeID> cell_nodes;
    const vector<vector<NodeID>>& id_map;
    const vector<NodeID>& real_map;
    const vector<vector<NodeID>>& a_result;
    vector<vector<NodeID>> phantom_nodes;
    vector<vector<NodeID>> result_cuts;

    // 替代无用引用成员参数, only for replacing members with empty vecs
    vector<NodeID> replace_vec;
    vector<vector<NodeID>> replace_vec_vec;

public:
    GraphPrinter(const vector<vector<NodeID>>& in_result, const vector<vector<NodeID>>& in_id_map, const vector<NodeID>& real_map, vector<EdgeID>& cellEdges, const int l): a_result(in_result), id_map(in_id_map), real_map(real_map), cell_edges(cellEdges), l(l), void_nodes(replace_vec){}
    GraphPrinter(const vector<NodeID>& void_nodes, vector<EdgeID>& cellEdges): void_nodes(void_nodes), cell_edges(cellEdges), id_map(replace_vec_vec), real_map(replace_vec), a_result(replace_vec_vec), l(0){}
    void write_void_result(mutex& w_lock, vector<vector<NodeID>>& res_cells_nodes, vector<vector<NodeID>>& res_cells_edges);
    void write_MLP_result(mutex& w_lock, vector<vector<NodeID>>& res_cells_nodes, vector<vector<NodeID>>& res_cells_edges, vector<vector<NodeID>>& res_void_cells);
    NodeID cuts_result_size(){return result_cuts.size();}
};
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

    unordered_map<NodeID, NodeID> node_cell;
    size_t contracted_cell_count = 0;
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
    }
    const NodeSize valid_cell_num = a_result.size() - contracted_cell_count;
    cout<<"contracted "<<contracted_cell_count<<" tiny iso cells\n";
    vector<vector<NodeID>> result_cells_edges(valid_cell_num);
    for (EdgeID eid = 0; eid < cell_edges.size()/2; eid++) {
        NodeID sid = cell_edges[2*eid];
        NodeID tid = cell_edges[2*eid+1];
        assert(node_cell.count(sid) && node_cell.count(tid));
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

//    ofstream outfile("/data/jjh/mlp_test/Graph-Partitioning-with-Natural-Cuts/logs/20211221/temp.txt");
//    outfile<<"nodes: ";
//    for (NodeID nid : result_cells_nodes[0])
//        outfile<<nid<<" ";
//    outfile<<"\n edges: ";
//    for (EdgeID eid = 0; eid < result_cells_edges[0].size()/2; eid++)
//        outfile<<"s: "<<result_cells_edges[0][eid*2]<<" t: "<<result_cells_edges[0][eid*2+1]<<"; ";
//    outfile<<"\n";

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

void GraphPrinter::write_void_result(mutex &w_lock, vector <vector<NodeID>> &res_cells_nodes,
                                     vector <vector<NodeID>> &res_cells_edges) {
    unordered_set<NodeID> cell_set;
    for (NodeID vid : void_nodes)
        cell_set.emplace(vid);
    vector<NodeID> result_edges;
    for (EdgeID eid = 0; eid < cell_edges.size()/2; eid++) {
        NodeID sid = cell_edges[eid*2];
        NodeID tid = cell_edges[eid*2+1];
        if (cell_set.count(sid) && cell_set.count(tid)) {
            result_edges.emplace_back(sid);
            result_edges.emplace_back(tid);
        }
    }
    unique_lock<mutex> write_lock(w_lock);
    res_cells_nodes.emplace_back(void_nodes);
    res_cells_edges.emplace_back(result_edges);
    write_lock.unlock();
}

#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_GRAPHPRINTER_H
