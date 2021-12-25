//
// Created by 骏辉 on 2021/10/12.
//
#include "../src/MLP/MultiLayerPartition.h"
//const int thread_limit = hardware_threads / 2;

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

//    bool accumulate = true;
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