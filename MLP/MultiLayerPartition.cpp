//
// Created by 骏辉 on 2021/10/12.
//

#include "MultiLayerPartition.h"
#include <ctime>

void MultiLayerPartition::MLP() {
    string in_edge_path = outPath + "layer-1_edges.txt";
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
    cout<<"Layer count: "<<this->getL()<<endl;
    for (int i = 0; i < this->getL(); i++) {
        for (int j = 0; j < this->ParaNum; j++) {
            int para;
            infile>>para;
            parameters[i].push_back(para);
        }
    }
//    vector<vector<vector<int>>> cell_nodes_list; // 后期可使用内存转储数据
//    vector<vector<vector<int>>> cut_edges_list;
    infile.close();
    infile.clear(ios::goodbit);

    unsigned int count;

    // read edges
    vector<vector<unsigned int>> graph_edges;
    infile.open(in_edge_path);
    if (!infile.is_open()) {
        cout<<"graph edge file open failed!\n";
        exit(1);
    }
    infile>>count;
    cout<<"Input graph has "<<count<<" edges\n";
    graph_edges.resize(count);
    for (int i = 0; i < count; i++) {
        unsigned int sid, tid;
        infile>>sid>>tid;
        graph_edges[i].push_back(sid);
        graph_edges[i].push_back(tid);
//            graph_edges[i].push_back(weight);
    }
    infile.close();
    infile.clear(ios::goodbit);

    // Bottom-up for now, needs to convert to top-down, change I/O logics.
    for (--l; l >= 0; l--) {
        cout<<"===========\n";
        if (phantom)
            cout<<"LAYER Phantom\n";
        else
            cout<<"LAYER "<<l+1<<endl;
        cout<<"===========\n";
        int prefix = l == getL() - 1 ? -1 : l + 2;
        if (prefix == -1 && !phantom) {
//            phantom = true;
        } else {
            phantom = false;
        }
        string last_layer = to_string(prefix);
        string cur_layer = to_string(l + 1);
        string out_node_path = outPath + "layer" + cur_layer + "_nodes.txt";
        string out_cut_path = outPath + "layer" + cur_layer + "_cuts.txt";
        vector<NodeID> void_nodes;
        U = parameters[l][0];
        C = parameters[l][1];
        FI = parameters[l][2];
        M = parameters[l][3];
        PS = parameters[l][4]; // 暂时默认PS = sqrt(M)
        cout<<"Layer "<<l + 1<<" parameters: U="<<U<<", C="<<C<<", FI="<<FI<<", M="<<M<<", PS="<<PS<<endl;
//        if (phantom) {
//            U = 32, C = 4, FI = 4, M = 4;
//            l++;
//            cout<<"Phantom layer parameters: U="<<U<<", C="<<C<<", FI="<<FI<<", M="<<M<<", PS="<<PS<<endl;
//        } else {
//            cout<<"Layer "<<l + 1<<" parameters: U="<<U<<", C="<<C<<", FI="<<FI<<", M="<<M<<", PS="<<PS<<endl;
//        }
//        string aNodePath = outPath + "anode_" + prefix + ".txt";
//        string aEdgePath = outPath + "aedge_" + prefix + ".txt";
        string in_node_path = outPath + "layer" + last_layer + "_nodes.txt";
        cout<<"input node: "<<in_node_path<<endl;
        if (phantom) {
            in_node_path = outPath + "layer0_nodes.txt";
            in_edge_path = outPath + "layer0_edges.txt";
        }
        // read nodes
        infile.open(in_node_path);
        if (!infile.is_open()) {
            cout<<"layer node file open failed!\n";
            exit(1);
        }
        ofstream outfile;
        // delete old files if any
        outfile.open(out_node_path);
        outfile.close();
        outfile.clear(ios::goodbit);
        outfile.open(out_cut_path);
        outfile.close();
        outfile.clear(ios::goodbit);

        unsigned int voidSize = 0, cellCount = 0, edgeCount = 0;
        infile>>voidSize;
        cout<<"current layer has "<<voidSize<<" void nodes.\n";
        for (int i = 0; i < voidSize; i++) {
            NodeID vid;
            infile>>vid;
            void_nodes.push_back(vid);
        }
        infile>>count;
        cout<<"current layer has "<<count<<" cells.\n";
        vector<vector<unsigned int>> cells;
        cells.reserve(count);
//        outfile.open(out_node_path, ios::app);
        for (int i = 0; i < count; i++) {
            unsigned int cellSize;
            infile >> cellSize;
            vector<unsigned int> cell_nodes;
            cell_nodes.reserve(cellSize);
            for (int j = 0; j < cellSize; j++) {
                unsigned int nid;
                infile >> nid;
                cell_nodes.push_back(nid);
            }
            cells.push_back(cell_nodes);
        }
        infile.close();
        infile.clear(ios::goodbit);

        cout<<"Nodes and edges read in succeed!\n";
        cout<<"Valid cells for next step: "<<count<<endl;

        int cell_count = 0;
        cout<<"cell size: "<<cells.size()<<endl;
        for (auto cell_iter = cells.begin(); cell_iter != cells.end(); cell_count++, cell_iter++) {
            if(cell_iter->size() < 32)
                continue;
            cout<<"------------\n";
            cout<<"CELL No."<<cell_count<<endl;
            cout<<"------------\n";
            bool* node_map = new bool[nodeNum](); // for finding edges in cell
            for (auto nid = cell_iter->begin(); nid != cell_iter->end(); nid++) {
//                cout<<"nid: "<<*nid<<endl;
                node_map[*nid] = 1;
            }
            cout<<"bit map finished\n";
            vector<vector<unsigned int>> cell_edges;
            vector<vector<unsigned int>> anodes;
            vector<vector<unsigned int>> aedges;

            vector<vector<unsigned int>> output_edges; // for ram storage

            //filter inner edges inside cell.
            for (vector<unsigned int> edge : graph_edges) {
                if (node_map[edge[0]] && node_map[edge[1]]) {
                    cell_edges.push_back(edge);
                }
            }
            cout<<cell_iter->size()<<" nodes, "<<cell_edges.size()<<" edges in cell_edges\n";
            Filter filter(U, C, *cell_iter, cell_edges, anodes, aedges);
            filter.runFilter();
            Assembly assembly(U, FI, M, false, anodes, aedges, outPath, phantom); // ttodo: convert file into bin type, delete outpath intake
            assembly.runAssembly();
//            PostProgress postProgress(anodes, cell_edges, cell_iter->size(), U);
//            postProgress.runPostProgress();
            bool need_contract = l == getL() - 1;
            GraphPrinter graphPrinter(assembly.get_result(), assembly.get_id_map(), *cell_iter, cell_edges, outPath, U, need_contract);
            graphPrinter.write_MLP_result(cur_layer, filter.get_real_map(), phantom);
            void_nodes.insert(void_nodes.end(), graphPrinter.get_cell_void_nodes().begin(), graphPrinter.get_cell_void_nodes().end());
            cellCount += graphPrinter.nodes_result_size();
            edgeCount += graphPrinter.cuts_result_size();
            cout<<"Cell processing completed, cell cnt:"<<cellCount<<" edgeCnt: "<<edgeCount<<endl;
        }
        // option: 改写为不读取size


        infile.open(out_node_path);
        string buffer((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>()); // read entire file
//        buffer = to_string(cellCount) + "\n" + buffer;
        infile.close();
        infile.clear(ios::goodbit);

        outfile.open(out_node_path);
        outfile<<void_nodes.size()<<" ";
        for (NodeID vid : void_nodes) {
            outfile<<vid<<" ";
        }
        outfile<<"\n"<<cellCount<<"\n"<<buffer;
        outfile.close();
        outfile.clear(ios::goodbit);

        infile.open(out_cut_path);
        string buffer2((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
        infile.close();
        infile.clear(ios::goodbit);

        outfile.open(out_cut_path);
        outfile<<edgeCount<<"\n"<<buffer2;
        outfile.close();
        outfile.clear(ios::goodbit);

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

    cout<<"Dealing with layer 0...\n";
    Preprocess preprocess(nodePath, edgePath, outPath);
    preprocess.runPreprocess();
    end = clock();
    int time = (end - start) / CLOCKS_PER_SEC;
    cout<<"Preprocess run time: "<<time<<"s.\n";


    MultiLayerPartition mlp(paraPath, outPath, preprocess.getNodeNum(), false);
    mlp.generateMLP();


//    AdaptivePrinter adaptivePrinter(outPath, 3, 723624);
    AdaptivePrinter adaptivePrinter(outPath, mlp.getL(), preprocess.getNodeNum());
    adaptivePrinter.filter_result();
    adaptivePrinter.print_final_result();
    adaptivePrinter.print_result_for_show(nodePath, edgePath);

    end = clock();
    time = (end - start) / CLOCKS_PER_SEC;
    cout<<"MLP run time: "<<time<<"s.\n";
}