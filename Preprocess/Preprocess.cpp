//
// Created by 骏辉 on 2021/10/8.
//
#include "Preprocess.h"

void preprocess(string co_path, string gr_graph, string out_path) {
    // preprocess nodes for assemble
    string co_out_path = "real_nodes.txt";
    string gr_out_path = "real_edges.txt";

    co_out_path.insert( co_out_path.begin(), out_path.begin(), out_path.end() );
    gr_out_path.insert( gr_out_path.begin(), out_path.begin(), out_path.end() );
    vector<navi::base::node_info_t> nodes;
    ifstream fs;
    fs.open(co_path, ios::binary);
    if (!fs.is_open()) {
        cout<<"co_file open failed!\n";
        exit(1);
    }
    ofstream os;
    os.open(co_out_path);
    if (!os.is_open()) {
        cout<<"co_out_file open failed!\n";
        exit(1);
    }
    uint32_t count;
    fs.read((char *)&count, sizeof(uint32_t));
    os<<count<<endl;
    nodes.resize(count);
    fs.read((char *)&nodes[0], sizeof(navi::base::node_info_t) * count);
    unsigned int counter = 0;
    auto node_iter = nodes.begin();
    for (; node_iter != nodes.end(); node_iter++) {
        if (counter % (count / 10) == 0) {
            cout<<counter * 100 / count<<"%\r";
        }
        os<<counter<<" "<<node_iter->geo_point.longitude<<" "<<node_iter->geo_point.latitude<<endl;
        counter++;
    }
    fs.close();
    fs.clear(ios::goodbit);
    os.close();
    os.clear(ios::goodbit);
    nodes.clear();

    // preprocess edges
    cout<<"preprocess edges...\n";
    std::vector<link_info_t> links;
    fs.open(gr_graph, ios::binary);
    if (!fs.is_open()) {
        cout<<"gr_file open failed!\n";
        exit(1);
    }
    os.open(gr_out_path);
    if (!os.is_open()) {
        cout<<"gr_out_file open failed!\n";
        exit(1);
    }
    fs.read((char *)&count, sizeof(uint32_t));
    links.resize(count);
    fs.read((char *)&links[0], sizeof(link_info_t) * count);
    counter = 0;
    auto edge_iter = links.begin();
    for (; edge_iter != links.end(); edge_iter++) {
        if (counter % (count / 10) == 0) {
            cout<<counter * 100 / count<<"%\r";
        }
        // using default weight=1;
        os<<edge_iter->start_node_id<<" "<<edge_iter->end_node_id<<endl;
        os<<edge_iter->end_node_id<<" "<<edge_iter->start_node_id<<endl;

        // use predefined weight
//        os<<edge_iter->start_node_id<<" "<<edge_iter->end_node_id<<" "<<edge_iter->forward_res_weigh<<endl;
//        os<<edge_iter->end_node_id<<" "<<edge_iter->start_node_id<<" "<<edge_iter->backward_res_weigh<<endl; // use predefined weight
        counter++;
    }
    links.clear();
    fs.close();
    os.close();
    cout<<"preprocess edges done\n";
}
int main(int argc, char** argv){
    clock_t start, end;
    start = clock();
    if( argc != 4 ){
        printf("usage:\n<arg1> origin nodes file path, e.g. C:/GraphPatition/data/node.txt\n");
        printf("<arg2> origin edge file path, e.g. C:/GraphPatition/data/edge.txt\n");
        printf("<arg3> output path, e.g. ../result/\n");
        exit(0);
    }
    string co_path( argv[1] );
    string gr_path( argv[2] );
    string out_path( argv[3] );
    preprocess(co_path, gr_path, out_path);
    cout<<"preprocess done\n";
    int time = (end - start) / CLOCKS_PER_SEC;
    cout<<"time spent: "<<time<<"s\n";
    return 0;
}


