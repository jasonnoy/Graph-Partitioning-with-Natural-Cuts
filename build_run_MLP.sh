#!/bin/bash
date_str=$(date +%Y%m%d)
time_str=$(date +%H%M%S)

if [ -d bin ]
then
  echo "bin file output dir ./bin"
else
  echo "creating dir bin, bin file output dir ./bin"
  mkdir bin
fi

if [ -d result ]
then
  echo "result output dir ./result"
else
  echo "creating dir result, result output dir ./result"
  mkdir result
fi

if [ -d logs ]
then
  echo "log dir ./logs"
else
  echo "creating log dir ./logs"
  mkdir logs
fi

if [ -d ./logs/"$date_str" ]
then
  echo "dir ./logs/$date_str exists"
else
  echo "creating dir ./logs/$date_str"
  mkdir "./logs/$date_str"
fi

if [ -f "./logs/$date_str/$time_str.log" ]
then
  echo "log ./logs/$date_str/$time_str.log exists, creating {$time_str}_1"
  echo "log output to .logs/$date_str/{$time_str}_1.log"
  touch ./logs/"$date_str"/"$time_str"_1.log || exit
else
  echo "log output to ./logs/$date_str/$time_str.log"
  touch ./logs/"$date_str"/"$time_str".log || exit
fi

g++ ./App/MultiLayerPartition.cpp -lpthread -o ./bin/MLP -std=c++11 > ./logs/"$date_str"/"$time_str".log 2>&1

#g++ ./MLP/MultiLayerPartition.cpp -g -lpthread ./MLP/Assembly.cpp ./MLP/Filter.cpp ./MLP/AdaptivePrinter.cpp ./MLP/Preprocess.cpp ./MLP/GraphPrinter.cpp ./common/Utility.cpp ./PUNCH/Filter/G_Graph.cpp ./PUNCH/Assemble/A_Graph.cpp -o ./bin/MLP -std=c++11 > ./logs/"$date_str"/"$time_str".log 2>&1

# base china input
#./bin/MLP ./data/paras.txt ./result/ 52 "$date_str$time_str" /data/map_data/rp_2.0/normal/2021_11_25_21_07_41/all/all/nodes /data/map_data/rp_2.0/normal/2021_11_25_21_07_41/all/all/links >> ./logs/"$date_str"/"$time_str".log 2>&1

#./bin/MLP ./data/paras.txt /data/jjh/partitions/1207/topo_node.hllnavi /data/jjh/partitions/1207/topo_link.hllnavi /data/jjh/partitions/1207/crp_weight_dist.hllnavi ./result/ 52 "$date_str$time_str" >> ./logs/"$date_str"/"$time_str".log 2>&1

# topo china test
#./bin/MLP ./data/paras.txt ./result/ 52 000 /data/jjh/crp_data/china/crp_weight_dist.hllnavi

# topo china input
./bin/MLP ./data/paras.txt ./result/ 60 "$date_str$time_str" /data/jjh/crp_data/china/crp_weight_dist.hllnavi >> ./logs/"$date_str"/"$time_str".log 2>&1

# Topo beijing input
#./bin/MLP ./data/paras_beijing.txt ./result/beijing/ 32 "$date_str$time_str" /data/jjh/mlp_test/Graph-Partitioning-with-Natural-Cuts/data/beijing/binary_data/crp_weight_dist.hllnavi >> ./logs/"$date_str"/"$time_str".log 2>&1

# base beijing input
# ./bin/MLP ./data/paras_beijing.txt ./result/beijing/ 32 "$date_str$time_str" /data/jjh/mlp_test/Graph-Partitioning-with-Natural-Cuts/data/beijing/binary_data/nodes /data/jjh/mlp_test/Graph-Partitioning-with-Natural-Cuts/data/beijing/binary_data/links >> ./logs/"$date_str"/"$time_str".log 2>&1

echo "Finished"