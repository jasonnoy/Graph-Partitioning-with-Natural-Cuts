//
// Created by 骏辉 on 2021/10/12.
//

#include "MultiLayerPartition.h"

// Parallel global variables.
condition_variable condition, file_condition;
mutex m_lock, file_lock;
const int thread_pool_capacity = 256; // the max threads that can be started at the same timed limited by linux system.
atomic<int> process_count(0);

const unsigned int hardware_threads = thread::hardware_concurrency();
//const int thread_limit = hardware_threads / 2;
int thread_limit = 1, current_occupied = 1;

// Parallel function
void dealCell(int processId, int extra_thread, int l, string cur_layer, vector<NodeID> &cell, atomic<int> &cellCount, atomic<int> &edgeCount, vector <NodeID> &void_nodes, const vector<vector<NodeID>>& graph_edges, const string outPath, const NodeID nodeNum, const int U, const int C, const int FI, const int M, const int L) {

    if (process_count > thread_limit-1) {
        unique_lock<mutex> lck(m_lock);
        while (process_count > thread_limit)
            condition.wait(lck);
    }
    process_count++;
    cout<<"Parallel dealing Thread ID: "<<processId<<endl;
    bool* node_map = new bool[nodeNum](); // for finding edges in cell
    for (NodeID nid : cell) {
        node_map[nid] = 1;
    }
//    cout<<"bit map finished\n";
    vector<vector<NodeID>> cell_edges;
    vector<vector<NodeID>> anodes;
    vector<vector<NodeID>> aedges;

    vector<vector<NodeID>> output_edges; // for ram storage

    //filter inner edges inside cell.
    for (vector<NodeID> edge : graph_edges) {
        if (node_map[edge[0]] && node_map[edge[1]]) {
            cell_edges.push_back(edge);
        }
    }

//    cout<<cell.size()<<" nodes, "<<cell_edges.size()<<" edges in cell_edges\n";
    Filter filter(U, C, extra_thread, cell, cell_edges, anodes, aedges, extra_thread);
    cout<<"Running filter...";
    filter.runFilter();
    Assembly assembly(U, FI, M, false, anodes, aedges, outPath, false); // ttodo: convert file into bin type, delete outpath intake
    cout<<"Running assembly...\n";
    assembly.runAssembly();
//            PostProgress postProgress(anodes, cell_edges, cell_iter->size(), U);
//            postProgress.runPostProgress();
    bool need_contract = l == L - 1;
    GraphPrinter graphPrinter(assembly.get_result(), assembly.get_id_map(), filter.get_real_map(), cell, cell_edges, outPath, U, need_contract);
    unique_lock<mutex> fileLock(file_lock); // mutex lock for printing
    graphPrinter.write_MLP_result(cur_layer, false);

//    cout<<"Thread "<<processId<<" Print finished\n";
    void_nodes.insert(void_nodes.end(), graphPrinter.get_cell_void_nodes().begin(), graphPrinter.get_cell_void_nodes().end());
    cellCount += graphPrinter.nodes_result_size();
    edgeCount += graphPrinter.cuts_result_size();
    process_count--;
    condition.notify_all();
    delete [] node_map;
}

void MultiLayerPartition::MLP() {
    cout<<"Server concurrency capacity: "<<thread::hardware_concurrency()<<endl;

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

    NodeID count;

    // read edges
    infile.open(in_edge_path);
    if (!infile.is_open()) {
        cout<<"graph edge file open failed!\n";
        exit(1);
    }
    infile>>count;
    cout<<"Input graph has "<<count<<" edges\n";
    graph_edges.resize(count);
    for (int i = 0; i < count; i++) {
        NodeID sid, tid;
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
//        if (l + 1 > 1) {
//            cout<<"not target, skip...\n";
//            continue;
//        }
        string out_node_path = outPath + "layer" + cur_layer + "_nodes.txt";
        string out_cut_path = outPath + "layer" + cur_layer + "_cuts.txt";
        // for test only!
//        if (cur_layer == "3") {
//            ifstream check(out_node_path);
//            if (check.good())
//                continue;
//        }
        //for test only!
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

        int voidSize = 0;
        atomic<int> cellCount(0);
        atomic<int> edgeCount(0);
        infile>>voidSize;
        cout<<"current layer has "<<voidSize<<" void nodes.\n";
        for (NodeID i = 0; i < voidSize; i++) {
            NodeID vid;
            infile>>vid;
            void_nodes.push_back(i);
        }
        infile>>count;
        cout<<"current layer has "<<count<<" cells.\n";
        vector<vector<NodeID>> cells;
        cells.reserve(count);
//        outfile.open(out_node_path, ios::app);
        for (int i = 0; i < count; i++) {
            NodeID cellSize;
            infile >> cellSize;
            vector<NodeID> cell_nodes;
            cell_nodes.reserve(cellSize);
            for (int j = 0; j < cellSize; j++) {
                NodeID nid;
                infile >> nid;
                cell_nodes.push_back(nid);
            }
            cells.push_back(cell_nodes);
        }
        infile.close();
        infile.clear(ios::goodbit);

        cout<<"Nodes and edges read in succeed!\n";
        cout<<"Valid cells for next step: "<<count<<endl;
        cout<<"cell size: "<<cells.size()<<endl;

        // Parallel
        vector<thread> ths;
        current_occupied = cells.size() > thread_limit ? thread_limit : cells.size();
        cout<<"cur occ: "<<current_occupied<<endl;
        int thread_left = cells.size();
        int thread_count = 0;
        int extra_thread = l==getL()-1? 4 : 1;
//        int extra_thread = thread_limit/current_occupied > 1 ? (thread_limit-2)/current_occupied : 1;
        cout<<"extra_thread: "<<extra_thread<<endl;
        while (thread_left > thread_pool_capacity) {
            for (int i = 0; i < thread_pool_capacity; i++) {
//            ParallelPunch parallelPunch(this, l, void_nodes);
//            ths.push_back(thread(&MultiLayerPartition::dealCell, this, l, cur_layer, cells[i], cellCount, edgeCount, void_nodes, process_count));
                ths.push_back(thread(dealCell, thread_count+i, extra_thread, l, cur_layer, ref(cells[thread_count+i]), ref(cellCount), ref(edgeCount), ref(void_nodes), ref(graph_edges), outPath, nodeNum, U, C, FI, M, L));
            }

            for (int i = 0; i < thread_pool_capacity; i++){
                ths[thread_count+i].join();
                cout<<thread_count+i<<"/"<<cells.size()<<" threads finished\n";
            }
            thread_left -= thread_pool_capacity;
            thread_count += thread_pool_capacity;
        }
        // now there is enough thread space for the rest threads
        for (int i = 0; i < thread_left; i++) {
            ths.push_back(thread(dealCell, thread_count+i, extra_thread, l, cur_layer, ref(cells[thread_count+i]), ref(cellCount), ref(edgeCount), ref(void_nodes), ref(graph_edges), outPath, nodeNum, U, C, FI, M, L));
        }
        for (int i = 0; i < thread_left; i++){
            ths[thread_count+i].join();
            cout<<thread_count+i<<"/"<<cells.size()<<" threads finished\n";
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
    if (argc != 6) {
        printf("usage:\n<arg1> parameter file path, e.g. C:/GraphPatition/data/paras.txt\n");
        printf("<arg2> node file path, e.g. C:/GraphPatition/data/node.txt\n");
        printf("<arg3> edge file path, e.g. C:/GraphPatition/data/edge.txt\n");
        printf("<arg4> result file directory, e.g. C:/GraphPatition/data/result/\n");
        printf("<arg4> number of thread, must be an positive integer\n");
        exit(0);
    }
    time_t start, end;
    start = time(&start);
    string paraPath(argv[1]);
    string nodePath(argv[2]);
    string edgePath(argv[3]);
    string outPath(argv[4]);
    thread_limit = stoi(argv[5]);
    if (thread_limit <= 0)
        thread_limit = 1;
    if (thread_limit > hardware_threads / 2) {
        cout<<"input thread setting surpass 1/2 of the max capacity, please enter an integer no bigger than "<<hardware_threads / 2<<endl;
        exit(0);
    }

    cout<<"Dealing with layer 0...\n";
    Preprocess preprocess(nodePath, edgePath, outPath);
    preprocess.runPreprocess();
    end = time(&end);
    long time_cost = end - start;
    cout<<"Preprocess run time: "<<time_cost<<"s.\n";


    MultiLayerPartition mlp(paraPath, outPath, preprocess.getNodeNum(), false);
    mlp.generateMLP();


//    AdaptivePrinter adaptivePrinter(outPath, 3, 723624);
    AdaptivePrinter adaptivePrinter(outPath, mlp.getL(), preprocess.getNodeNum());
    adaptivePrinter.filter_result();
    adaptivePrinter.print_final_result();
//    adaptivePrinter.print_result_for_show(nodePath, edgePath);

    end = time(&end);
    time_cost = end - start;
    cout<<"MLP run time: "<<time_cost<<"s.\n";
}