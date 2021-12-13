//
// Created by 骏辉 on 2021/10/12.
//

#include "MultiLayerPartition.h"
#include "../Common/io_util.h"

// Parallel global variables.
const int thread_pool_capacity = 256; // the max threads that can be started at the same timed limited by linux system.
atomic<int> process_count(0);

const unsigned int hardware_threads = thread::hardware_concurrency();
//const int thread_limit = hardware_threads / 2;
int thread_limit = 1, current_occupied = 1;

// Parallel function
void dealCell(mutex& w_lock, int extra_thread, int l, string cur_layer, vector<NodeID>& thread_index, vector<vector<NodeID>> &cells_nodes, atomic<int> &cutCount, vector<vector<NodeID>>& res_void_cells, vector<vector<vector<EdgeID>>>& cells_edges, vector<vector<NodeID>> &res_cells_nodes, vector<vector<vector<EdgeID>>>& res_cells_edges, const NodeID nodeNum, const int U, const int Uf, const int C, const int FI, const int M, const int L) {
    time_t start, mid, end;
    cout<<"Node num: "<<nodeNum<<"\n";
    for (NodeID cell_id:thread_index) {
        time(&start);
        process_count++;
        cout<<"Parallel dealing Cell: "<<process_count<<"/"<<cells_nodes.size()<<endl;
        vector<NodeID>& cell = cells_nodes[cell_id];
        vector<vector<EdgeID>>& cell_edges = cells_edges[cell_id];
        cout<<"cell edge size: "<<cell_edges.size()<<endl;
        vector<vector<NodeID>> anodes;
        vector<vector<NodeID>> aedges;
        vector<vector<NodeID>> output_edges; // for ram storage

        time(&mid);
        cout<<"cell preprocess time: "<<mid-start<<"s\n";

        Filter filter(Uf, U, C, cell, cell_edges, anodes, aedges, extra_thread);
        cout<<"Running filter...";
        filter.runFilter();
        Assembly assembly(U, FI, M, false, anodes, aedges, false);
        cout<<"Running assembly...\n";
        assembly.runAssembly();

        time(&mid);
        bool need_contract = l == L - 1;
        GraphPrinter graphPrinter(assembly.get_result(), assembly.get_id_map(), filter.get_real_map(), cell, cell_edges, U, need_contract);
        graphPrinter.write_MLP_result(res_cells_nodes, res_cells_edges, res_void_cells, w_lock);
//        void_cells.insert(void_cells.end(), graphPrinter.get_void_cells().begin(), graphPrinter.get_void_cells().end());

//        cellCount += graphPrinter.nodes_result_size();
        cutCount += graphPrinter.cuts_result_size();

        time(&end);
        cout<<"cell print time cost: "<<end-mid<<"s, "<<"cell time cost: "<<end-start<<"s\n";
    }
}

void MultiLayerPartition::read_graph(const string topo_node_path, const string topo_weight_path) {
//    ofstream outfile;
//    string out_node_path = out_path + "layer0_nodes.txt";
//    string out_edge_path = out_path + "layer0_edges.txt";
//    string out_node_path = out_path + "layer-1_nodes.txt";
//    string out_edge_path = out_path + "layer-1_edges.txt";

    vector<topo_node_info_t> topo_nodes;

    topo_link_head_weight_t* topo_link_weight_head = read_topo_link(topo_weight_path);
    size_t node_count = topo_link_weight_head->max_vertex_id+1;

    vector<NodeID> graph_nodes;
    graph_nodes.reserve(node_count);

    for (NodeID i = 0; i < node_count; i++)
        graph_nodes.emplace_back(i);
    cells_nodes.emplace_back(graph_nodes);

    nodeNum = node_count;
    node_parti.reserve(nodeNum);

    size_t edge_count = topo_link_weight_head->total_topo_link;
    edge_weight_t* topo_edge_weight_ptr = &topo_link_weight_head->topo_link_weight;
    cout<<"There are "<<edge_count<<" edges in layer 0\n";

    vector<vector<EdgeID>> graph_edges;
    graph_edges.resize(edge_count);

    for (size_t i = 0; i < edge_count; i++) {
        edge_weight_t& link = topo_edge_weight_ptr[i];
        graph_edges[link.s_node_].push_back(link.e_node_);
        graph_edges[link.e_node_].push_back(link.s_node_);
    }
    cells_edges.emplace_back(graph_edges);

//    outfile.close();
//    outfile.clear(ios::goodbit);
}

void MultiLayerPartition::MLP() {
    time_t begin, mid, finish;
    time(&begin);
    cout<<"Server concurrency capacity: "<<thread::hardware_concurrency()<<endl;
    size_t total_cell_num = 0;
    size_t total_cut_num = 0;

//    string in_edge_path = outPath + "layer-1_edges.txt";
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
    infile.close();
    infile.clear(ios::goodbit);
    time(&finish);
    cout<<"mlp preprocess time: "<<finish-begin<<"s\n";

//
//    vector<vector<vector<int>>> cell_nodes_list; // 后期可使用内存转储数据
//    vector<vector<vector<int>>> cut_edges_list;
    // read edges
//    infile.open(in_edge_path);
//    if (!infile.is_open()) {
//        cout<<"graph edge file open failed!\n";
//        exit(1);
//    }
//    graph_edges.resize(nodeNum);
//    infile>>count;
//    cout<<"Input graph has "<<count<<" edges\n";
//    for (int i = 0; i < count; i++) {
//        NodeID sid, tid;
//        infile>>sid>>tid;
//        graph_edges[sid].push_back(tid);
////            graph_edges[i].push_back(weight);
//    }
//    infile.close();
//    infile.clear(ios::goodbit);

    for (--l; l >= 0; l--) {
        time_t start, end;
        time(&start);
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
//        if (l + 1 > 4) {
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
        Uf = parameters[l][1];
        C = parameters[l][2];
        FI = parameters[l][3];
        M = parameters[l][4];
        PS = parameters[l][5]; // 暂时默认PS = sqrt(M)
        cout<<"Layer "<<l + 1<<" parameters: U="<<U<<", Uf="<<Uf<<", C="<<C<<", FI="<<FI<<", M="<<M<<", PS="<<PS<<endl;
//        if (phantom) {
//            U = 32, C = 4, FI = 4, M = 4;
//            l++;
//            cout<<"Phantom layer parameters: U="<<U<<", C="<<C<<", FI="<<FI<<", M="<<M<<", PS="<<PS<<endl;
//        } else {
//            cout<<"Layer "<<l + 1<<" parameters: U="<<U<<", C="<<C<<", FI="<<FI<<", M="<<M<<", PS="<<PS<<endl;
//        }
//        string aNodePath = outPath + "anode_" + prefix + ".txt";
//        string aEdgePath = outPath + "aedge_" + prefix + ".txt";
//        string in_node_path = outPath + "layer" + last_layer + "_nodes.txt";
//        cout<<"input node: "<<in_node_path<<endl;
//        if (phantom) {
//            in_node_path = outPath + "layer0_nodes.txt";
//            in_edge_path = outPath + "layer0_edges.txt";
//        }
        // read nodes
//        infile.open(in_node_path);
//        if (!infile.is_open()) {
//            cout<<"layer node file open failed!\n";
//            exit(1);
//        }
//        ofstream outfile;
//        // delete old files if any
//        outfile.open(out_node_path);
//        outfile.close();
//        outfile.clear(ios::goodbit);
//        outfile.open(out_cut_path);
//        outfile.close();
//        outfile.clear(ios::goodbit);

        int voidSize = 0;
        atomic<int> cellCount(0);
        atomic<int> cutCount(0);
//        infile>>voidSize;
//        cout<<"current layer has "<<voidSize<<" void nodes.\n";
//        for (NodeID i = 0; i < voidSize; i++) {
//            NodeID vid;
//            infile>>vid;
//            void_nodes.push_back(i);
//        }
        NodeSize count;

//        infile>>count;
//        cout<<"current layer has "<<count<<" cells.\n";
//        vector<vector<NodeID>> cells;
//        cells.reserve(count);
//        vector<vector<vector<NodeID>>> cells_edges;
//        cells_edges.resize(count);
//        for (int i = 0; i < count; i++) {
//            cout<<"processing cell no."<<i<<"/"<<count<<"\r";
//            NodeID cellSize;
//            infile >> cellSize;
//            vector<NodeID> cell_nodes;
//            cell_nodes.reserve(cellSize);
//            unordered_set<NodeID> cell_node_set;
//            for (int j = 0; j < cellSize; j++) {
//                NodeID nid;
//                infile >> nid;
//                cell_nodes.push_back(nid);
//                cell_node_set.emplace(nid);
//            }
//            cells.push_back(cell_nodes);
//            for (NodeID sid : cell_nodes) {
//                if (sid >= graph_edges.size()) {
//                    cout<<"sid: "<<sid<<", cell size: "<<cell_nodes.size()<<endl;
//                    cout<<"nodes: ";
//                    for (NodeID nid:cell_nodes)
//                        cout<<nid<<" ";
//                    cout<<endl;
//                }
//
//                for (NodeID tid : graph_edges[sid]) {
//                    if (cell_node_set.count(tid)) {
//                        vector<NodeID> edge = {sid, tid};
//                        cells_edges[i].push_back(edge);
//                    }
//                }
//            }
//        }
//        infile.close();
//        infile.clear(ios::goodbit);

        cout<<"Nodes and edges read in succeed!\n";
//        cout<<"Valid cells for next step: "<<count<<endl;
        cout<<"cell size: "<<cells_nodes.size()<<endl;

        // Parallel
        vector<thread> ths;
        current_occupied = cells_nodes.size() > thread_limit ? thread_limit : cells_nodes.size();
        cout<<"cur occ: "<<current_occupied<<endl;
//        int thread_left = cells_nodes.size();
//        int thread_count = 0;
//        int extra_thread = l==getL()-1? 10 : 1;
        int extra_thread = thread_limit/current_occupied > 1 ? thread_limit/current_occupied : 1;
        cout<<"extra_thread: "<<extra_thread<<endl;
        vector<vector<NodeID>> thread_index(current_occupied);
        for (NodeID i = 0 ; i < cells_nodes.size(); i++) {
            thread_index[i%current_occupied].push_back(i);
        }
        mutex file_lock;
        for (size_t i = 0; i < current_occupied; i++)
            ths.push_back(thread(dealCell, ref(file_lock), extra_thread, l, cur_layer,ref(thread_index[i]), ref(cells_nodes), ref(cutCount), ref(void_cells), ref(cells_edges), ref(res_cells_nodes), ref(res_cells_edges), nodeNum, U, Uf, C, FI, M, L));
        for (int i = 0; i < current_occupied; i++){
            ths[i].join();
            cout<<i<<"/"<<current_occupied<<" threads finished\n";
        }

        cout<<"Writing layer partition result...\n";
        for (size_t i = 0; i < res_cells_nodes.size(); i++) {
            for (NodeID nid : res_cells_nodes[i])
                node_parti[nid].emplace_back(i);
        }
        cout<<"Done\n";

        cell_sizes.emplace_back(res_cells_nodes.size());
        cout<<"Layer "<<l<<" has "<<res_cells_nodes.size()<<"cells, "<<cutCount.load()<<" cuts\n";
        total_cell_num += res_cells_nodes.size();
        total_cut_num += cutCount.load();

        process_count = 0;
        cells_nodes = res_cells_nodes;
        cells_edges = res_cells_edges;
        res_cells_nodes.clear();
        res_cells_edges.clear();

        time(&end);
        cout<<"layer time cost: "<<end-start<<"s\n";

//
//        while (thread_left > thread_pool_capacity) {
//            for (int i = 0; i < thread_pool_capacity; i++) {
////            ParallelPunch parallelPunch(this, l, void_nodes);
////            ths.push_back(thread(&MultiLayerPartition::dealCell, this, l, cur_layer, cells[i], cellCount, edgeCount, void_nodes, process_count));
//                ths.push_back(thread(dealCell, thread_count+i, extra_thread, l, cur_layer, ref(cells[thread_count+i]), ref(cellCount), ref(edgeCount), ref(void_nodes), ref(graph_edges), outPath, nodeNum, U, Uf, C, FI, M, L));
//            }
//
//            for (int i = 0; i < thread_pool_capacity; i++){
//                ths[thread_count+i].join();
//                cout<<thread_count+i<<"/"<<cells.size()<<" threads finished\n";
//            }
//            thread_left -= thread_pool_capacity;
//            thread_count += thread_pool_capacity;
//        }
        // now there is enough thread space for the rest threads
//        for (int i = 0; i < thread_left; i++) {
//            ths.push_back(thread(dealCell, thread_count+i, extra_thread, l, cur_layer, ref(cells[thread_count+i]), ref(cellCount), ref(edgeCount), ref(void_nodes), ref(graph_edges), outPath, nodeNum, U, Uf, C, FI, M, L));
//        }
//        for (int i = 0; i < thread_left; i++){
//            ths[thread_count+i].join();
//            cout<<thread_count+i<<"/"<<cells.size()<<" threads finished\n";
//        }

        // option: 改写为不读取size
//        infile.open(out_node_path);
//        string buffer((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>()); // read entire file
////        buffer = to_string(cellCount) + "\n" + buffer;
//        infile.close();
//        infile.clear(ios::goodbit);
//
//        outfile.open(out_node_path);
////        outfile<<void_nodes.size()<<" ";
////        for (NodeID vid : void_nodes) {
////            outfile<<vid<<" ";
////        }
//
//        outfile.close();
//        outfile.clear(ios::goodbit);
//
//        infile.open(out_cut_path);
//        string buffer2((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
//        infile.close();
//        infile.clear(ios::goodbit);
//
//        outfile.open(out_cut_path);
//
//        outfile.close();
//        outfile.clear(ios::goodbit);

    }
    // deal void cells
    for (size_t i = 0; i < void_cells.size(); i++) {
        NodeID index = total_cell_num + i;
        for (NodeID vid : void_cells[i])
            node_parti[vid].emplace_back(index);
    }
    time(&finish);
    cout<<"mlp time cost: "<<finish-begin<<"s\n";
}

void MultiLayerPartition::print_parti(const string timestamp) {
    time_t start, end;
    time(&start);
    const string file_path = outPath+"node_partitions_"+timestamp+".txt";
    ofstream outfile;
    outfile.open(file_path);
    if (!outfile.is_open()) {
        cout<<"partition file open failed\n";
        exit(-1);
    }
    outfile<<L<<endl;
    for (size_t layer_size : cell_sizes)
        outfile<<layer_size<<endl;
    outfile<<nodeNum<<endl;
    for (auto node_cids : node_parti){
        for (auto cid : node_cids) {
            outfile<<cid<<" ";
        }
        outfile<<endl;
    }
    time(&end);
    cout<<"Print partition time cost: "<<end-start<<endl;
}

int main(int argc, char** argv) {
    if (argc != 8) {
        printf("usage:\n<arg1> parameter file path, e.g. C:/GraphPatition/data/paras.txt\n");
        printf("<arg2> node file path, e.g. C:/GraphPatition/data/node.txt\n");
        printf("<arg3> edge file path, e.g. C:/GraphPatition/data/edge.txt\n");
        printf("<arg4> weight file path, e.g. C:/GraphPatition/data/weight.txt\n");
        printf("<arg5> result file directory, e.g. C:/GraphPatition/data/result/\n");
        printf("<arg6> number of thread, must be an positive integer\n");
        printf("<arg7> timestamp needed\n");
        exit(0);
    }
    time_t start, end;
    start = time(&start);
    string paraPath(argv[1]);
    string nodePath(argv[2]);
    string edgePath(argv[3]);
    string weightPath(argv[4]);
    string outPath(argv[5]);
    thread_limit = stoi(argv[6]);
    string timestamp(argv[7]);
    if (thread_limit <= 0)
        thread_limit = 1;
    if (thread_limit > hardware_threads / 2) {
        cout<<"Notice: input thread setting surpass 1/2 of the max capacity, which is  "<<hardware_threads / 2<<endl;
    }
    if (thread_limit > hardware_threads) {
        cout<<"Notice: input thread setting surpass the max capacity, which is  "<<hardware_threads<<endl;
        exit(0);
    }

//    cout<<"Dealing with layer 0...\n";
//    Preprocess preprocess(nodePath, edgePath, weightPath, outPath);
//    preprocess.runPreprocess();
//    end = time(&end);
//    cout<<"Preprocess run time: "<<end-start<<"s.\n";


    MultiLayerPartition mlp(paraPath, outPath, false);
    mlp.read_graph(nodePath, edgePath);
    mlp.generateMLP();
    mlp.print_parti(timestamp);


//    AdaptivePrinter adaptivePrinter(outPath, 3, 723624);
//    AdaptivePrinter adaptivePrinter(outPath, 6, preprocess.getNodeNum());
//    vector<vector<NodeID>> void_temp;
//    adaptivePrinter.filter_result(void_temp); // temp only

//    AdaptivePrinter adaptivePrinter(outPath, mlp.getL(), preprocess.getNodeNum());
//    adaptivePrinter.filter_result(mlp.get_void_cells());
//    cout<<"printing final result..\n";
//    adaptivePrinter.print_final_result(timestamp);
//    adaptivePrinter.print_result_for_show(nodePath, edgePath);

    end = time(&end);
    cout<<"MLP run time: "<<end-start<<"s.\n";
}