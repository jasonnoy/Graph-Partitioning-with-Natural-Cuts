//
// Created by 骏辉 on 2021/10/12.
//

#include "MultiLayerPartition.h"

void MultiLayerPartition::MLP() {
    const string aNodePath = outPath + "anode.txt";
    const string aEdgePath = outPath + "aedge.txt";
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
    // Bottom-up for now, needs to convert to top-down, change I/O logics.
    auto layer_iter = parameters.begin();
    for (; layer_iter != parameters.end(); layer_iter++) {
        int U, C, FI, M, PS;    // 暂时默认PS = sqrt(M)
        cout<<"Running filter phase...\n";
        Filter filter(U, C, coPath, grPath, outPath);
        filter.runFilter();
        cout<<"Filter phase completed!\n";
        cout<<"Running assembly phase...\n";
        Assembly assembly(U, FI, M, false, coPath, grPath, aNodePath, aEdgePath, outPath);
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
    string paraPath(argv[1]);
    string nodePath(argv[2]);
    string edgePath(argv[3]);
    string outPath(argv[4]);
    MultiLayerPartition mlp(paraPath, nodePath, edgePath, outPath);
    mlp.generateMLP();
}