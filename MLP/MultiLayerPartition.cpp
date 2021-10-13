//
// Created by 骏辉 on 2021/10/12.
//

#include "MultiLayerPartition.h"
#include <ctime>

void MultiLayerPartition::MLP() {
    const string aNodePath = outPath + "anode.txt";
    const string aEdgePath = outPath + "aedge.txt";
    const string realNodePath = outPath + "real_nodes.txt";
    const string realGraphPath = outPath + "real_edges.txt";
    ifstream infile;
    infile.open(paraPath);
    if (!infile.is_open()) {
        cout<<"Open para file failed!\n";
        exit(1);
    }
    int l;
    infile>>l;
    this->setL(l);
    parameters.resize(this->getL());
    cout<<"Layer number: "<<this->getL()<<endl;
    for (int i = 0; i < this->getL(); i++) {
        for (int j = 0; j < this->ParaNum; j++) {
            int para;
            infile>>para;
            parameters[i].push_back(para);
        }
    }
    infile.close();
    // Bottom-up for now, needs to convert to top-down, change I/O logics.
    for (--l; l >= 0; l--) {
        int U, C, FI, M, PS;
        U = parameters[l][0];
        C = parameters[l][1];
        FI = parameters[l][2];
        M = parameters[l][3];
        PS = parameters[l][4]; // 暂时默认PS = sqrt(M)
        cout<<"Layer "<<getL()<<" parameters: U="<<U<<", C="<<C<<", FI="<<FI<<", M="<<M<<", PS="<<PS<<endl;
        cout<<"Running filter phase...\n";
        Filter filter(U, C, coPath, grPath, outPath);
//        filter.runFilter();
//        filter.~Filter();
        cout<<"Filter phase completed!\n";
        cout<<"Running assembly phase...\n";
        Assembly assembly(U, FI, M, false, realNodePath, realGraphPath, aNodePath, aEdgePath, outPath);
        assembly.runAssembly();
        cout<<"Assembly phase completed!\n";
    }
}

int main(int argc, char** argv) {
    if (argc != 5) {
        printf("usage:\n<arg1> parameter file path, e.g. C:/GraphPatition/data/paras.txt\n");
        printf("<arg2> node file path, e.g. C:/GraphPatition/data/node.txt\n");
        printf("<arg3> edge file path, e.g. C:/GraphPatition/data/edge.txt\n");
        printf("<arg4> result file directory, e.g. C:/GraphPatition/data/result/\n");
        exit(0);
    }
    clock_t start, end;
    start = clock();
    string paraPath(argv[1]);
    string nodePath(argv[2]);
    string edgePath(argv[3]);
    string outPath(argv[4]);
    MultiLayerPartition mlp(paraPath, nodePath, edgePath, outPath);
    mlp.generateMLP();
    end = clock();
    int time = (end - start) / CLOCKS_PER_SEC;
    cout<<"MLP run time: "<<time<<"s.\n";
}