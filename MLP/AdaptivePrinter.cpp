//
// Created by 骏辉 on 2021/10/19.
//

#include "AdaptivePrinter.h"
void AdaptivePrinter::filter_result() {
    for (int l = 1; l <= layer; l++) {
        string layer_node_path = out_path + "layer" + to_string(l) + "_nodes.txt";
        ifstream infile;
        infile.open(layer_node_path);
        infile>>cell_nums[l-1];
        vector<unsigned int> temp(layer);
        node_parti.resize(node_num, temp);
        cout<<"layer "<<to_string(l)<<" has "<<cell_nums[l-1]<<" cells.\n";
        for (int cell_count = 0; cell_count < cell_nums[l-1]; cell_count++) {
            int node_size;
            infile>>node_size;
            for (int i = 0; i < node_size; i++) {
                unsigned int nid;
                infile>>nid;
                node_parti[nid][l-1] = cell_count;
            }
        }
    }
    // filter edges.
}

void AdaptivePrinter::print_result_for_show(const string node_path, const string edge_path) {
    ifstream infile;
    infile.open(node_path, ios::binary);

    vector<node_info_t> nodes;
    unsigned int count;
    infile.read((char*)&count, sizeof(uint32_t));
    if (count != node_num) {
        cout<<"count != code_num\n";
    }
    nodes.resize(node_num);
    infile.read((char *)&nodes[0], sizeof(node_info_t) * node_num);
    infile.close();
    infile.clear(ios::goodbit);

    for (int l = 1; l <= layer; l++) {
        const string layer_nodes = out_path + "layer" + to_string(l) + "_nodes.txt";
        const string result_nodes = out_path + "layer" + to_string(l) + "_node_co.txt";
        infile.open(layer_nodes);
        ofstream outfile;
        outfile.open(result_nodes);

        int cell_num;
        infile>>cell_num;
        for (int i = 0; i < cell_num; i++) {
            int node_size;
            infile>>node_size;
            for (int j = 0; j<node_size; j++) {
                unsigned int nid;
                infile>>nid;
                outfile<<nodes[nid].geo_point.latitude<<","<<nodes[nid].geo_point.longitude<<";";
            }
            outfile<<"\n";
        }
        infile.close();
        infile.clear(ios::goodbit);
        outfile.close();
        outfile.clear(ios::goodbit);
    }
}
void AdaptivePrinter::print_final_result() {
    string filtered_nodes_path = out_path + "result_nodes.txt";
    string result_path = out_path + "node_partitions.txt";

    ofstream outfile, outfile2;
    outfile.open(result_path);
    outfile2.open(filtered_nodes_path);

    outfile<<layer<<endl;
    for (int num : cell_nums) {
        outfile<<num<<"\n";
    }


    vector<unsigned int> filtered_nodes;
    for (unsigned int nid = 0; nid < node_num; nid++) {
        for (int l = 0; l < layer; l++) {
            outfile<<node_parti[nid][l]<<" ";
        }
        outfile<<"\n";
        filtered_nodes.push_back(nid);
//        if (node_parti[nid][0] || node_parti[nid][1] || node_parti[nid][2]) {
//            for (int l = 0; l < layer; l++) {
//                outfile<<node_parti[nid][l] - 1<<" ";
//            }
//            outfile<<"\n";
//            filtered_nodes.push_back(nid);
//        }
    }
    outfile2<<filtered_nodes.size()<<"\n";
    for (auto node_iter = filtered_nodes.begin(); node_iter != filtered_nodes.end(); node_iter++) {
        outfile2<<*node_iter<<"\n";
    }
}