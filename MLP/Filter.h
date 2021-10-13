//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H

#include "../Filter/G_Graph.h"
#include <ctime>
#include <stdlib.h>

using namespace std;

class Filter {
private:
    G_Graph gGraph;
    const int U;
    const int C;
    int F = 10;
    const string NodePath;
    const string GraphPath;
    const string OutPath;

    void read_in_graph();
    void contract_tiny_cuts();
    void contract_natural_cuts();
    void convert_and_output();
public:
    Filter(int u, int c, const string nPath, const string gPath, const string oPath): U(u), C(c), NodePath(nPath), GraphPath(gPath), OutPath(oPath){
    };
    Filter(int u, int c, int f, const string nPath, const string gPath, const string oPath): U(u), C(c), F(f), NodePath(nPath), GraphPath(gPath), OutPath(oPath){
    };
    ~Filter() = default;
    void runFilter();
    int getF(){return F;}
    void setF(int f){F = f;}
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_FILTER_H
