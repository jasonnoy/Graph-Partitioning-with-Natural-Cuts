//
// Created by 骏辉 on 2021/10/19.
//

#include "AdaptivePrinter.h"
void AdaptivePrinter::filter_result() {
    read_phantom_nodes();

    for (int l = 1; l <= layer; l++) {
        string layer_node_path = out_path + "layer" + to_string(l) + "_nodes.txt";
        ifstream infile;
        infile.open(layer_node_path);
        int void_size;
        infile>>void_size;
        vector<unsigned int> void_nodes;
        void_nodes.reserve(void_size);
        for (int i = 0; i < void_size; i++) {
            unsigned int vid;
            infile>>vid;
            void_nodes.push_back(vid);
        }
        infile>>cell_nums[l-1];
        vector<int> temp(layer);
        node_parti.resize(node_num + void_size, temp);
        cout<<"layer "<<to_string(l)<<" has "<<cell_nums[l-1]<<" cells.\n";
        for (int cell_count = 0; cell_count < cell_nums[l-1]; cell_count++) {
            int node_size;
            infile>>node_size;
            for (int i = 0; i < node_size; i++) {
                unsigned int nid;
                infile>>nid;
                for (unsigned int real_id:phantom_nodes[nid])
                    node_parti[real_id][l-1] = cell_count;
//                node_parti[nid][l-1] = cell_count;
            }
        }
        for (unsigned int vid : void_nodes) {
            for (unsigned int real_vid:phantom_nodes[vid])
                node_parti[real_vid][l-1] = -1;
//            node_parti[vid][l-1] = -1;
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

        int cell_num, void_num;
        infile>>void_num;
        for (int i = 0; i < void_num; i++) {
            unsigned int vid;
            infile>>vid;
        }
        infile>>cell_num;
        for (int i = 0; i < cell_num; i++) {
            int node_size;
            infile>>node_size;
            for (int j = 0; j < node_size; j++) {
                unsigned int nid;
                infile>>nid;
                for (unsigned int real_id:phantom_nodes)
                    outfile<<nodes[real_id].geo_point.latitude<<","<<nodes[real_id].geo_point.longitude<<";";
            }
            outfile<<"\n";
        }
        infile.close();
        infile.clear(ios::goodbit);
        outfile.close();
        outfile.clear(ios::goodbit);
    }
}

void AdaptivePrinter::read_phantom_nodes() {
    string phantom_path = out_path + "phantom_nodes.txt";
    ifstream infile;
    infile.open(phantom_path);
    unsigned int phantom_size;
    infile>>phantom_size;
    phantom_nodes.resize(phantom_size);
    for (unsigned int i = 0; i < phantom_size; i++) {
        unsigned int node_size;
        infile>>node_size;
        phantom_nodes[i].reserve(node_size);
        for (unsigned int j = 0; j < node_size; j++) {
            unsigned int nid;
            infile>>nid;
            phantom_nodes[i].push_back(nid);
        }
    }
    cout<<"Read phantom nodes done\n";
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
    }
    outfile2<<filtered_nodes.size()<<"\n";
    for (auto node_iter = filtered_nodes.begin(); node_iter != filtered_nodes.end(); node_iter++) {
        outfile2<<*node_iter<<"\n";
    }
}