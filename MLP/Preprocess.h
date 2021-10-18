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
#include "Assembly.h"
#include "Filter.h"

using namespace std;

class Preprocess {
private:
    void preprocess();
    int nodeNum = 0;
    int edgeNum = 0;
public:
    const string sw_node_path;
    const string sw_link_path;
    const string out_path;
    Preprocess(const string node_path, const string link_path, const string o_path):sw_node_path(node_path),sw_link_path(link_path),out_path(o_path){};
    void runPreprocess(){preprocess();}
    unsigned int getNodeNum(){return nodeNum;}
    unsigned int getEdgeNum(){return edgeNum;}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_PREPROCESS_H
