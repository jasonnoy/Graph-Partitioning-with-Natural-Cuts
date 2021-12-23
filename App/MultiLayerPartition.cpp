//
// Created by 骏辉 on 2021/10/12.
//
#include "../src/MLP/MultiLayerPartition.h"


// Parallel global variables.
const int thread_pool_capacity = 256; // the max threads that can be started at the same timed limited by linux system.
atomic<int> process_count(0);

const unsigned int hardware_threads = thread::hardware_concurrency();
//const int thread_limit = hardware_threads / 2;
int thread_limit = 1, current_occupied = 1;

// Parallel function
void dealCell(mutex& n_lock, int extra_thread, int l, vector<NodeID>& thread_index, vector<vector<NodeID>> &cells_nodes, atomic<int> &cutCount, vector<vector<NodeID>>& res_void_cells, vector<vector<EdgeID>>& cells_edges, vector<vector<NodeID>> &res_cells_nodes, vector<vector<EdgeID>>& res_cells_edges, const int U, const int Uf, const int C, const int FI, const int M) {
    time_t start, mid, end;
    for (NodeID cell_id:thread_index) {
        time(&start);
        process_count++;
        cout<<"Parallel dealing Cell: "<<process_count<<"/"<<cells_nodes.size()<<endl;
        vector<NodeID>& cell = cells_nodes[cell_id];
        vector<EdgeID>& cell_edges = cells_edges[cell_id];
        cout<<"cell node size: "<<cell.size()<<", cell edge size: "<<cell_edges.size()/2<<endl;

        if (cell.size() < U) {
            cout<<"cell size less than U, hand over to next layer\n";
            GraphPrinter graphPrinter(cell, cell_edges);
            graphPrinter.write_void_result(n_lock, res_cells_nodes, res_cells_edges);
            continue;
        }
        assert(!cell_edges.empty());
//        if (cell_edges.empty()) {
//            unique_lock<mutex> node_lock(n_lock);
//            res_cells_nodes.emplace_back(cell);
//            node_lock.unlock();
//            cout<<"empty cell edge, skipping..\n";
//            continue;
//        }
        vector<vector<NodeID>> anodes;
        vector<vector<NodeID>> aedges;
//        vector<vector<NodeID>> output_edges; // for ram storage

        time(&mid);
        cout<<"cell preprocess time: "<<mid-start<<"s\n";

        Filter filter(Uf, U, C, cell, cell_edges, anodes, aedges, extra_thread);
        cout<<"Running filter...";
        filter.runFilter();
        cout<<"Filter result node size: "<<anodes.size()<<", edge size: "<<aedges.size()<<endl;
        Assembly assembly(U, FI, M, false, anodes, aedges, false);
        cout<<"Running assembly...\n";
        assembly.runAssembly();

        time(&mid);
        GraphPrinter graphPrinter(assembly.get_result_nodes(), assembly.get_id_map(), filter.get_real_map(), cell_edges, l);
        graphPrinter.write_MLP_result( n_lock, res_cells_nodes, res_cells_edges, res_void_cells);
//        void_cells.insert(void_cells.end(), graphPrinter.get_void_cells().begin(), graphPrinter.get_void_cells().end());

//        cellCount += graphPrinter.nodes_result_size();
//        cutCount += graphPrinter.cuts_result_size();

        time(&end);
        cout<<"cell print time cost: "<<end-mid<<"s, "<<"cell time cost: "<<end-start<<"s\n";
    }
}

int main(int argc, char** argv) {
    if (argc != 7 && argc != 6) {
        printf("usage:\n<arg1> parameter file path, e.g. C:/GraphPatition/data/paras.txt\n");
        printf("<arg2> weight file path, e.g. C:/GraphPatition/data/weight.txt\n");
        printf("<arg3> result file directory, e.g. C:/GraphPatition/data/result/\n");
        printf("<arg4> number of thread, must be an positive integer\n");
        printf("<arg5> timestamp needed\n");
        printf("topo or base: <arg6> topo file path, e.g. C:/GraphPatition/data/topo_weight.txt\n");
        printf("topo or base: <arg6> node file path, e.g. C:/GraphPatition/data/node.txt\n");
        printf("topo or base: <arg7> edge file path, e.g. C:/GraphPatition/data/edge.txt\n");
        exit(0);
    }
    time_t start, end;
    start = time(&start);
    string paraPath(argv[1]);
    string outPath(argv[2]);
    thread_limit = stoi(argv[3]);
    string timestamp(argv[4]);
    string topoPath, nodePath, edgePath;
    bool topo = true;
    if (argc == 6) {
        topoPath = argv[5];
        cout<<"reading topo file: "<<topoPath<<endl;
    } else {
        topo = false;
        nodePath = argv[5];
        edgePath = argv[6];
        cout<<"reading base node: "<<nodePath<<", base link: "<<edgePath<<endl;
    }
    if (thread_limit <= 0)
        thread_limit = 1;
    if (thread_limit > hardware_threads / 2) {
        cout<<"Notice: input thread setting surpass 1/2 of the max capacity, which is  "<<hardware_threads / 2<<endl;
    }
    if (thread_limit > hardware_threads) {
        cout<<"Notice: input thread setting surpass the max capacity, which is  "<<hardware_threads<<endl;
        exit(0);
    }

    MultiLayerPartition mlp(paraPath, outPath, false);
    if (topo) {
        mlp.read_topo_graph(topoPath);
    } else {
        mlp.read_base_graph(nodePath, edgePath);
    }

    bool accumulate = true;
    const string partition_file_path = "/data/jjh/partitions/1220/node_partitions_20211217221805.txt";
//    const int ori_layer = 5;
    const int base_layer = 3;
    if (accumulate) {
        time_t begin, end;
        time(&begin);
        mlp.read_accumu_parti(partition_file_path, base_layer);
        time(&end);
        cout<<"read accumu parti used "<<end-begin<<"s\n";
    }
//    cout<<"read in graph finished, check mem\n";
//    sleep(15);
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