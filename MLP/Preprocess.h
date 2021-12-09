//
// Created by 骏辉 on 2021/10/13.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_PREPROCESS_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_PREPROCESS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "../Common/sw_basetypes.h"
#include "../Common/tp_basetype.h"
#include "../Common/Utility.h"
#include "../Common/crp_types.h"
#include "../Common/io_util.h"
#include "Assembly.h"
#include "Filter.h"

using namespace std;

typedef navi::base::topo_node_t topo_node_info_t;
typedef navi::base::topo_link_t topo_link_info_t;
typedef navi::base::topo_link_head_t topo_link_head_t;

class Preprocess {
private:
    void preprocess();
    int nodeNum = 0;
    int edgeNum = 0;
public:
    const string sw_node_path;
    const string sw_link_path;
    const string topo_node_path;
    const string topo_link_path;
    const string out_path;
    const string topo_weight_path;
    Preprocess(const string node_path, const string link_path, const string o_path):sw_node_path(node_path),sw_link_path(link_path),out_path(o_path){};
    Preprocess(const string tp_node_path, const string tp_link_path, const string tp_weight_path, const string o_path):topo_node_path(tp_node_path),topo_link_path(tp_link_path), topo_weight_path(tp_weight_path), out_path(o_path){};
    void runPreprocess(){preprocess();}
    NodeID getNodeNum(){return nodeNum;}
    NodeID getEdgeNum(){return edgeNum;}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_PREPROCESS_H
