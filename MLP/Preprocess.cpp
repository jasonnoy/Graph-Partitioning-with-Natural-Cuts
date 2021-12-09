//
// Created by 骏辉 on 2021/10/13.
//

#include "Preprocess.h"
#include <ctime>
#include <string>

void Preprocess::preprocess() {
    ifstream infile;
    ofstream outfile;
//    string out_node_path = out_path + "layer0_nodes.txt";
//    string out_edge_path = out_path + "layer0_edges.txt";
    string out_node_path = out_path + "layer-1_nodes.txt";
    string out_edge_path = out_path + "layer-1_edges.txt";

//    infile.open(sw_node_path, std::ios::binary);
//
//    if (!infile.is_open()) {
//        cout<<"sw_node_file open failed!\n";
//        exit(1);
//    }
//    outfile.open(out_node_path);
//    if (!outfile.is_open()) {
//        cout<<"out_node_file open failed!\n";
//        exit(1);
//    }
//
////    outfile<<"0\n"; // empty void nodes
//    uint32_t count;
//    infile.read((char *)&count, sizeof(uint32_t));
//    nodeNum = count;
//    cout<<"There are "<<count<<" nodes in layer 0\n";
//    outfile<<"1\n"<<count<<" ";
//    for (int i = 0; i < count; i++) {
//        outfile<<i<<" ";
//    }
//    infile.close();
//    infile.clear(ios::goodbit);
    vector<topo_node_info_t> topo_nodes;
//    read_binary(topo_node_path, topo_nodes);
//    ifstream fs(topo_node_path, ios::binary);
//    if (!fs){
//        cerr << "open file failed: " << path << endl;
//        return -1;
//    }
//    uint32_t count;
//    fs.read((char *)&count, sizeof(uint32_t));
//    outfile<<count<<endl;
//    fs.close();
//    fs.clear(ios::goodbit);
//
//    for (size_t i = 0; i < count; i++)
//        outfile<<i<<endl;

    topo_link_head_weight_t* topo_link_weight_head = read_topo_link(topo_weight_path);
    size_t node_count = topo_link_weight_head->max_vertex_id+1;

    outfile.open(out_node_path);

    for (size_t i = 0; i < node_count; i++)
        outfile<<i<<endl;
    outfile.close();
    outfile.clear(ios::goodbit);

    size_t edge_count = topo_link_weight_head->total_topo_link;
    edge_weight_t* topo_edge_weight_ptr = &topo_link_weight_head->topo_link_weight;
    cout<<"There are "<<edge_count<<" edges in layer 0\n";

    outfile.open(out_edge_path);

    outfile<<edge_count<<endl;
    for (size_t i = 0; i < edge_count; i++) {
        edge_weight_t& link = topo_edge_weight_ptr[i];
        outfile<<link->s_node_<<"\n"<<link->e_node_<<endl;
    }

    outfile.close();
    outfile.clear(ios::goodbit);

//
//    // read in edges
//    std::vector<navi::base::link_info_t> links;
//    infile.open(sw_link_path, std::ios::binary);
//    if (!infile.is_open()) {
//        cout<<"gr_file open failed!\n";
//        exit(1);
//    }
//
//    outfile.open(out_edge_path);
//    if (!outfile.is_open()) {
//        cout<<"out_edge_file open failed!\n";
//        exit(1);
//    }
//    infile.read((char *)&count, sizeof(uint32_t));
//    edgeNum = count;
//    cout<<"There are "<<count<<" edges in layer 0\n";
//    links.resize(count);
//    infile.read((char *)&links[0], sizeof(navi::base::link_info_t) * count);
//    outfile<<count * 2<<endl;
//    for (auto edge_iter = links.begin(); edge_iter != links.end(); edge_iter++) {
//        outfile<<edge_iter->start_node_id<<" "<<edge_iter->end_node_id<<" ";
//        outfile<<edge_iter->end_node_id<<" "<<edge_iter->start_node_id<<" ";
////        outfile<<edge_iter->start_node_id<<" "<<edge_iter->end_node_id<<" "<<edge_iter->forward_res_weigh<<" "; //目前假设weight为1
////        outfile<<edge_iter->end_node_id<<" "<<edge_iter->start_node_id<<" "<<edge_iter->backward_res_weigh<<" ";
//    }
//    infile.close();

}

//int main(int argc, char* argv[]) {
//    if (argc != 4) {
//        printf("usage:\n<arg1> sw_node file path, e.g. ../data/node.txt\n");
//        printf("<arg2> sw_link file path, e.g. e.g. ../data/link.txt\n");
//        printf("<arg3> output path, e.g. ../result/\n");
//        exit(0);
//    }
//    clock_t start, end;
//    start = clock();
//    cout<<"Preprocessing layer 0...\n";
//    string sw_nodes(argv[1]);
//    string sw_links(argv[2]);
//    string output(argv[3]);
//    Preprocess preprocess(sw_nodes, sw_links, output);
//    preprocess.runPreprocess();
//    end = clock();
//    int time = (end - start) / CLOCKS_PER_SEC;
//    cout<<"Preprocess run time: "<<time<<"s.\n";
//    return 0;
//}