//
// Created by 骏辉 on 2021/11/11.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_PHANTOM_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_PHANTOM_H

#include "../../common/common.h"
#include "../../common/sw_basetypes.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Phantom {
private:
    const NodeID total_node_num;
    const string out_path;
    NodeID ph_node_Num = 0;
    vector<NodeID> nid_to_phId;
    vector<vector<NodeID>> phId_to_nids;
    vector<vector<NodeID>> phEdge;
public:
    Phantom(const string outPath, const NodeID nodeNum) : out_path(outPath), total_node_num(nodeNum) {};
    ~Phantom() = default;

    void read_Phantom_Graph(const string phantom_path) {
        cout<<"Reading phantom graph: "<<phantom_path<<endl;

        nid_to_phId.resize(total_node_num);

        ifstream infile;
        infile.open(phantom_path);

        NodeID count;
        infile>>count;
        if (count) {
            cout<<count<<" void nodes in phantom graph\n";
            for (NodeID i = 0; i < count; i++)
        }
        nodeNum = count;

        infile.read((char *)&sw_nodes[0], sizeof(navi::base::node_info_t) * node_num);
        infile.close();
        infile.clear(ios::goodbit);

        NodeID nid_size = 0;
        phId_to_nids.resize(nodeNum);
        for (NodeID i = 0; i < nodeNum; i++) {
            for (NodeID nid : )
        }

        const string out_node_path = out_path + "layer-1_nodes.txt";
        ofstream outfile;
        outfile.open(out_node_path);
        outfile<<0<<endl<<1<<nodeNum<<endl;
        for (NodeID i = 0; i < nodeNum; i++)
            outfile<<i<<" ";
        outfile.close();
        outfile.clear(ios::goodbit);

    }
};
#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_PHANTOM_H
