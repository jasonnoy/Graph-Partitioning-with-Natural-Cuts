//
// Created by 骏辉 on 2021/10/12.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H

#include "../Assemble/A_Graph.h"
#include "../Assemble/R_Graph.h"

class Assembly {
private:
    int FI = 16;
    int M = 1;
    bool COMBINE = false;

    vector<vector<NodeID>> result;
    vector<vector<NodeID>> id_map;
    R_Graph real_graph;
    A_Graph a_graph;

    void read_a_graph();
    void multistart_and_combination();
    void write_result();
public:
    const int U;
    const string nodePath;
    const string graphPath;
    const string aNodePath;
    const string aGraphPath;
    const string outPath;

    Assembly(int u, const string nPath, const string gPath, const string aNPath, const string aGPath, const string oPath):
        U(u), nodePath(nPath), graphPath(gPath), aNodePath(aNPath), aGraphPath(aGPath), outPath(oPath){};
    Assembly(int u, int fi, int m, bool combine, const string nPath, const string gPath, const string aNPath, const string aGPath, const string oPath):
    U(u), FI(fi), M(m), COMBINE(combine), nodePath(nPath), graphPath(gPath), aNodePath(aNPath), aGraphPath(aGPath), outPath(oPath){};
    void runAssembly();
};


#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ASSEMBLY_H
